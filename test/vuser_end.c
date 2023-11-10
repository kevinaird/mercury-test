int randomVar;

vuser_end()
{
	int i;
	randomVar = 1;

	{
		randomVar = 2;
	}

	for(i=0;i<5;i++) {
		randomVar = i;
	}
	
	return 0;
}
