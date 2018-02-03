struct MemoryRegion
{
  void *startAddr;
  void *endAddr;
  int isReadable;
  int isWriteable;
  int isExecutabl;
};

int printStruct(struct MemoryRegion *mr);

int printStruct(struct MemoryRegion *mr)
{
	printf("MemoryRegion:{\n");
	printf("\tstartAddr:%p\n"  , mr -> startAddr);
    printf("\tendAddr:%p\n"    , mr -> endAddr);
    printf("\tisReadable:%d\n" , mr -> isReadable);
    printf("\tisWriteable:%d\n", mr -> isWriteable);
    printf("\tisExecutabl:%d\n", mr -> isExecutabl);
	printf("}\n");
};