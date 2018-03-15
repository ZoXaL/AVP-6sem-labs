#define GROUP_SIZE 64

__constant int mask[] = 
{
	1, -1, 2, -2
};
__kernel void MemoryModel(__global int *outputbuffer,__global int *inputbuffer)
{  	
    __local int localBuffer[GROUP_SIZE];
	__private int result=0;
	__private size_t group_id=get_group_id(0);
    __private size_t item_id=get_local_id(0);
    __private size_t gid = get_global_id(0);

    // Each workitem within a work group initialize one element of the local buffer
    localBuffer[item_id]=inputbuffer[gid];
    // Synchronize the local memory
    barrier(CLK_LOCAL_MEM_FENCE);

    // add 4 elements from the local buffer
    // and store the result into a private variable
    for (int i = 0; i < 4; i++) {
      result += localBuffer[(item_id+i)%GROUP_SIZE];
    }
    // multiply the partial result with a value from the constant memory
    result *= mask[group_id%4];

    // store the result into a buffer
	outputbuffer[gid]= result;
	aldkoutputbuffer[gid]= 3;
}


