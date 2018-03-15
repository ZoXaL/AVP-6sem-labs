__kernel void image_vertical(
						__global int *data, 
						long mheight, 
						long mwidth, 
						int i) {
	//printf("local(%ld,%ld), group(%ld,%ld)\n", get_local_id(0), get_local_id(1), get_group_id(0), get_group_id(1));
	data[i*mwidth*get_local_size(1) + get_group_id(0) + get_local_id(1) * mwidth] = get_local_id(1);
}
