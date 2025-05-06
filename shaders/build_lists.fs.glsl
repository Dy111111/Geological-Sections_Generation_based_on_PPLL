#version 430 core

layout (early_fragment_tests) in;

struct NodeType {
  uint color;
  float depth;
  uint next;
};

layout (binding = 0, r32ui) uniform uimage2D head_pointer_image;
//layout (binding = 1, rg32ui) uniform writeonly uimageBuffer list_buffer;
layout( binding = 0, std430 ) buffer linkedLists {
  NodeType nodes[];
};

layout (binding = 0, offset = 0) uniform atomic_uint list_counter;
uniform uint MaxNodes;

layout (location = 0) out vec4 color;

struct Light {
    vec3 position;  
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
	
    float constant;
    float linear;
    float quadratic;
};
 //从Mtl中读取的数据
//Material
in vec4 Ambient;
in vec4 Diffuse;
in vec4 Specular;
 
uniform vec3 viewPos;
uniform Light light;
 
uniform float shininess;

uniform uint side;

in vec3 frag_position;
in vec3 frag_normal;

void main(void)
{
    uint index;
    uint old_head;
    uvec2 item;
    vec4 frag_color;

    vec4 final=Diffuse+vec4(0.2,0.2,0.2,0);
    index = atomicCounterIncrement(list_counter);
    if( index< MaxNodes ) {
    float depth=gl_FragCoord.z;
    if(side==1) depth=-depth;
    // Our fragment will be the new head of the linked list, so
    // replace the value at gl_FragCoord.xy with our new node's
    // index.  We use imageAtomicExchange to make sure that this
    // is an atomic operation.  The return value is the old head
    // of the list (the previous value), which will become the
    // next element in the list once our node is inserted.
    old_head = imageAtomicExchange(head_pointer_image, ivec2(gl_FragCoord.xy), uint(index));

    // Here we set the color and depth of this new node to the color
    // and depth of the fragment.  The next pointer, points to the
    // previous head of the list.
    nodes[index].color = packUnorm4x8(final);
    nodes[index].depth = depth;
    nodes[index].next = old_head;
  }
    

    vec4 modulator = Diffuse;
    //vec4 additive_component = mix(modulator, vec4(1.0), 0.6) * vec4(pow(clamp(NdotH, 0.0, 1.0), 26.0)) * 0.7;
    

    frag_color = modulator;

    color = frag_color;
}
