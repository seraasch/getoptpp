The following example shows format manipulators usage to enter hex numbers.

```
int main(int argc, char* argv[])
{
	int i;
	
	GetOpt_pp ops(argc, argv);
	
	ops >> std::hex >> Option('i', "number", i);
	
	std::cout << std::hex << "Number entered: (hex)" << i << " (dec)" << std::dec << i << std::endl;
	
	return 0;
}
```