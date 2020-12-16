// Mai Trần Khánh Duy
// MSSV: 20127684
// Ex 4: Hãy khai báo kiểu dữ liệu để biểu diễn khái niệm đa thức một biến trong toán học

#include<stdio.h>
#include<conio.h>
#include<math.h>
#define MAX 100
#define E(x, i) x.HeSo[i]
struct DonThuc
{
	float HeSo;
	int SoMu;
};
typedef struct DonThuc DONTHUC;
struct DaThuc
{
	float HeSo[MAX];
	int SoMu;
};
typedef struct DaThuc DATHUC;

void KhoiTaoDaThucRong(DATHUC &);
void NhapDaThuc(DATHUC &);
void XuatDaThuc(DATHUC, char[]);


DATHUC TinhHieu2DaThuc(DATHUC, DATHUC);
DATHUC TinhTong2DaThuc(DATHUC, DATHUC);
DATHUC TinhTich2DaThuc(DATHUC, DATHUC);
DATHUC TinhThuong2DaThuc(DATHUC, DATHUC);
DATHUC TinhDaThucDu(DATHUC, DATHUC);
DATHUC TinhDaoHamCap1(DATHUC);
DATHUC TinhDaoHamCapk(DATHUC);
float TinhGiaTri(DATHUC, float);
float TimNghiemDaThucTrongDoanAB(float, float);

DATHUC operator +(DATHUC, DATHUC);
DATHUC operator -(DATHUC, DATHUC);
DATHUC operator *(DATHUC, DATHUC);
DATHUC operator /(DATHUC, DATHUC);


DATHUC TinhDaoHamCap1(DATHUC);
DATHUC TinhDaoHamCapk(DATHUC, int);
float TinhDaoHamCapk(DATHUC, float);

// Dinh nghia ham
void KhoiTaoDaThucRong(DATHUC &dt)
{
	dt.SoMu = 0;
	for (int i = 0; i < MAX; i++)
		dt.HeSo[i] = 0;
}
void NhapDaThuc(DATHUC &dt)
{
	KhoiTaoDaThucRong(dt);
	do
	{
		printf("\n Nhap bac da thuc: ");
		scanf_s("%d", &dt.SoMu);
		if (dt.SoMu < 1)
		{
			printf("\n So bac cua da thuc phai >= 1. Xin kiem tra lai !");
		}
	} while (dt.SoMu < 1);

	for (int i = dt.SoMu; i >= 0; i--)
	{
		float temp;
		printf("\n Nhap he so: ");
		scanf_s("%f", &temp);
		dt.HeSo[i] = temp;
	}
}

void XuatDaThuc(DATHUC dt, char thongbao[])
{
	printf("%s", thongbao);
	for (int i = dt.SoMu; i > 0; i--)
	{
		if (dt.HeSo[i] != 0)
		{
			printf("%8.3fx^%d + ", dt.HeSo[i], i);
		}
	}
	printf("%8.3f\n", dt.HeSo[0]);
}


// Tính tổng 2 đa thức
DATHUC TinhTong2DaThuc(DATHUC a, DATHUC b)
{
	DATHUC ketqua;
	KhoiTaoDaThucRong(ketqua);

	if (a.SoMu > b.SoMu)
	{
		ketqua.SoMu = a.SoMu;  
	}
	else
	{
		ketqua.SoMu = b.SoMu;
	}

	for (int i = 0; i <= ketqua.SoMu; i++)
	{
		ketqua.HeSo[i] = a.HeSo[i] + b.HeSo[i];
	}
	return ketqua;
}

// Tính hiệu đa thức
DATHUC TinhHieu2DaThuc(DATHUC a, DATHUC b)
{
	DATHUC ketqua;
	KhoiTaoDaThucRong(ketqua);

	// xét bậc đa thức kết quả
	// nếu bậc đa thức a lớn hơn bậc đa thức b
	if (a.SoMu > b.SoMu)
	{
		ketqua.SoMu = a.SoMu;  // bậc đa thức kết quả là bậc đa thức a
	}
	else
	{
		ketqua.SoMu = b.SoMu;
	}
	// xét hệ số đa thức kết quả:
	for (int i = 0; i <= ketqua.SoMu; i++)
	{
		ketqua.HeSo[i] = a.HeSo[i] - b.HeSo[i];
	}
	return ketqua;
}

// Tính tích 2 đa thức
DATHUC TinhTich2DaThuc(DATHUC a, DATHUC b)
{
	DATHUC ketqua;
	KhoiTaoDaThucRong(ketqua);

	ketqua.SoMu = a.SoMu + b.SoMu;

	int i, j;
	for (i = 0; i <= a.SoMu; i++)
	{
		for (j = 0; j <= b.SoMu; j++)
		{
			ketqua.HeSo[i + j] += a.HeSo[i] * b.HeSo[j];
		}
	}
	return ketqua;
}

// Tính thương 2 đa thức
DATHUC TinhThuong2DaThuc(DATHUC a, DATHUC b)
{
	DATHUC ketqua;
	KhoiTaoDaThucRong(ketqua);

	ketqua.SoMu = a.SoMu + b.SoMu;

	int i, j;
	for (i = 0; i <= a.SoMu; i++)
	{
		for (j = 0; j <= b.SoMu; j++)
		{
			ketqua.HeSo[i + j] += a.HeSo[i] / b.HeSo[j];
		}
	}
	return ketqua;
}

// Tính đạo hàm cấp 1 đa thức
DATHUC TinhDaoHamCap1(DATHUC dt)
{
	DATHUC ketqua;
	KhoiTaoDaThucRong(ketqua);

	ketqua.SoMu = dt.SoMu - 1;

	for (int i = dt.SoMu; i >= 0; i--)
	{
		ketqua.HeSo[i - 1] = dt.HeSo[i] * i;
	}
	return ketqua;
}

// Tính đạo hàm cấp k của đa thức
DATHUC TinhDaoHamCapk(DATHUC dt, int k)
{
	DATHUC ketqua = dt;
	for (int i = 0; i < k; i++)
	{
		ketqua = TinhDaoHamCap1(ketqua);
	}
	return ketqua;
}

int main()
{
	int k;
	DATHUC dt1, dt2;
	DATHUC ResultK;
	NhapDaThuc(dt1);
	XuatDaThuc(dt1, "\n Da thuc 1: ");
	printf("\n---------------");
	NhapDaThuc(dt2);
	XuatDaThuc(dt2, "\n Da thuc 2: ");
	printf("\n---------------");
	XuatDaThuc(TinhTong2DaThuc(dt1, dt2), "\n Da thuc 1 + Da thuc 2 = ");
	XuatDaThuc(TinhHieu2DaThuc(dt1, dt2), "\n Da thuc 1 - Da thuc 2 = ");
	XuatDaThuc(TinhTich2DaThuc(dt1, dt2), "\n Da thuc 1 * Da thuc 2 = ");
	XuatDaThuc(TinhThuong2DaThuc(dt1, dt2), "\n Da thuc 1 / Da thuc 2 = ");
	XuatDaThuc(TinhDaoHamCap1(dt1), "\n Dao ham cap 1 = ");
	do
	{
		printf("\n\n Nhap k: ");
		scanf_s("%d", &k);
		if (k < 0 || k > dt2.SoMu)
		{
			printf("\n\n k khong hop le. Xin nhap lai!");
		}
	} while (k < 0 || k > dt2.SoMu);

	ResultK = TinhDaoHamCapk(dt2, k);
	printf("\n Dao ham cap %d cua don thuc = %8.3fx^%d", k, ResultK.HeSo, ResultK.SoMu);
	_getch();
	return 0;
}
