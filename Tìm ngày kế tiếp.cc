struct Ngay
{
	int Day, Month, Year;
};
typedef struct Ngay NGAY;

void InputDay(NGAY &);
void OutputDay(NGAY);

NGAY TimNgayKeDoKNgay(NGAY, int);

// Tìm ngày kế đó k ngày //
NGAY TimNgayKeDoKNgay(NGAY a, int k)
{
	while (k > 0)
	{
		a = TimNgayKeTiep(a);
		k--;
	}
	return a;
}

int main()
{
  int k;
  printf("\n   Nhap vao k: ");
	scanf_s("%d", &k);

	printf("\n   Ngay ke tiep %d ngay la ngay: ",k);
	OutputDay(TimNgayKeDoKNgay(a, k));
}

