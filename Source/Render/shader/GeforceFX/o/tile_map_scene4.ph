static DWORD shader[]={
	0xffff0200, 0x05000051, 0xa00f0004, 0x3e800000, 0x3e800000, 0x3e800000, 
	0x3e800000, 0x05000051, 0xa00f0000, 0x3f000000, 0x3f000000, 0x3f000000, 
	0x3f800000, 0x05000051, 0xa00f0001, 0x3f000000, 0x3f000000, 0x3f000000, 
	0x00000000, 0x0200001f, 0x80000000, 0xb00f0000, 0x0200001f, 0x80000000, 
	0xb00f0001, 0x0200001f, 0x80000000, 0xb00f0002, 0x0200001f, 0x80000000, 
	0xb00f0003, 0x0200001f, 0x90000000, 0xa00f0800, 0x0200001f, 0x90000000, 
	0xa00f0801, 0x0200001f, 0x90000000, 0xa00f0802, 0x0200001f, 0x90000000, 
	0xa00f0803, 0x03000042, 0x800f0000, 0xb0e40003, 0xa0e40803, 0x02000001, 
	0x802f0800, 0x80e40000, 0x0000ffff, 
};
	Compile("tile_map_scene4.psh",shader);