#version 430 core
//layout (early_fragment_tests) in;
struct NodeType {
  uint color;
  float depth;
  uint next;
};
// The per-pixel image containing the head pointers
layout (binding = 0, r32ui) uniform uimage2D head_pointer_image;

// Buffer containing linked lists of fragments
layout( binding = 0, std430 ) buffer linkedLists {
  NodeType nodes[];
};
// This is the maximum number of overlapping fragments allowed
#define MAX_FRAGMENTS 90

// Temporary array used for sorting fragments


layout (location = 0) out vec4 color;
uniform vec2 resolution;


float near = 1.0; 
float far = 1000.0; 
float LinearizeDepth(float depth) 
{
    float z = depth * 2.0 - 1.0; // back to NDC 
    return (2.0 * near * far) / (far + near - z * (far - near));	
}
void main(void)
{  
    NodeType targetFragment;//对应地层节点
    targetFragment.depth=1.0;
    uint current_index;//像素链表头结点索引
    uint fragment_count = 0;//节点个数计数器
    int count=0;//射线法计数器
    current_index=imageLoad(head_pointer_image,
    ivec2(gl_FragCoord).xy).x;//获得当前像素头结点索引
    
    while(current_index != 0&&fragment_count<MAX_FRAGMENTS){
        NodeType fragment = nodes[current_index];
        float depth=fragment.depth;
        current_index = fragment.next;
        if(abs(depth)>gl_FragCoord.z){
            float curdepth=abs(targetFragment.depth);
            if(depth>0){
                if(abs(depth)<curdepth) 
                    targetFragment=fragment;
                count--;
               }
            else count++;
        }
        fragment_count++;
    }
    if(count!=0)
        color =unpackUnorm4x8(targetFragment.color); 
    else
        discard;

}
