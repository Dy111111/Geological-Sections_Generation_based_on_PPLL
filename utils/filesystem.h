
#ifndef FILESYSTEM_H
#define FILESYSTEM_H
#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include <cstdlib>



class FileSystem
{
private:
  typedef std::string (*Builder) (const std::string& path);

public:
  static std::string getPath(const std::string& path)
  {
    static std::string(*pathBuilder)(std::string const &) = getPathBuilder();
    return (*pathBuilder)(path);
  }

private:
    static std::string const& getRoot()
    {
        static char envRoot[256];
        static size_t envRootSize = 0;
        static bool isEnvRootInitialized = false;

        if (!isEnvRootInitialized)
        {
            char* tempEnvRoot = nullptr;
            size_t tempEnvRootSize = 0;
            errno_t err = _dupenv_s(&tempEnvRoot, &tempEnvRootSize, "LOGL_ROOT_PATH");

            if (err == 0 && tempEnvRoot != nullptr)
            {
                strncpy_s(envRoot, 256, tempEnvRoot, tempEnvRootSize);
                envRootSize = tempEnvRootSize;
                free(tempEnvRoot);
            }

            isEnvRootInitialized = true;
        }

        static char const* givenRoot = (envRootSize != 0 ? envRoot : "E:/Ex/Final Work/added/model_clipping");
        static std::string root = givenRoot;
        return root;
    }


  //static std::string(*foo (std::string const &)) getPathBuilder()
  static Builder getPathBuilder()
  {
    if (getRoot() != "")
      return &FileSystem::getPathRelativeRoot;
    else
      return &FileSystem::getPathRelativeBinary;
  }

  static std::string getPathRelativeRoot(const std::string& path)
  {
    return getRoot() + std::string("/") + path;
  }

  static std::string getPathRelativeBinary(const std::string& path)
  {
    return "../../../" + path;
  }


};

// FILESYSTEM_H
#endif
