int GetCode(int BigCode)
{
	if (BigCode < 100) return BigCode;
	if (BigCode < 1000) return BigCode % 10;
	if (BigCode < 10'000) return BigCode % 100;
	return BigCode % 1'000;
}

int GetFirstParameterMode(int BigCode)
{
	return (BigCode / 100) % 10;
}

int GetSecondParameterMode(int BigCode)
{
	return (BigCode / 1000) % 10;
}

int GetThirdParameterMode(int BigCode)
{
	return (BigCode / 10000) % 10;
}

int NumberOfParameters(int code)
{
	switch (code)
	{
	case 1: case 2: case 7: case 8:
		return 3;

	case 3: case 4:
		return 1;

	case 5: case 6:
		return 2;
	case 9:
		return 1;
	}
}

long long int GetResult(int code, long long int first, long long int second)
{
	switch (code)
	{
	case 1:
		return first + second;
	case 2:
		return first * second;
	case 4:
		return first;
	case 7:
		if (first < second) return 1;
		else return 0;
	case 8:
		if (first == second) return 1;
		else return 0;
	case 9:
		return first;
	default:
		return 0;
	}
}