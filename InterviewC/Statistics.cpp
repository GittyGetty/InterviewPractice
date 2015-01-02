

float locker_room_chances(int n, int x) {
	float p = 100;
	float nf = (float)n;

	for (int i = 1; i <= x; ++i)
		p *= 1 - 2 / (nf - i);

	return 100 - p;
}
