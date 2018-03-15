__kernel void memset( __global int *ds) {
	ds[get_global_id(0)] = 2;
}
