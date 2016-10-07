
void list_Spaces(struct list_s* list)
{
	int i;
	int number = 0;
	for (i = 0; i < list->length; i++)
	{
		if ((int)list->line[i] == 32))
		{
			number++;
		}
	}
	
	if (number > 5)
	{
		for (i = 0; i < list->length; i++)
		{
			if ((int)list->line[i] == 32))
			{
				list->line[i] = '_';
			}
		}
	}
}