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
}#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h>

#define SUITS 4
#define FACES 13

using namespace std;

const char* suits[SUITS] = { "Hearts", "Diamonds", "Clubs", "Spades" };
const char* faces[FACES] = { "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King", "Ace" };

void shuffleCards(int deck[][FACES])
{
	for (int i = 0; i < SUITS; i++)
	for (int j = 0; j < FACES; j++)
		deck[i][j] = 0;

	for (int i = 0; i < 52; i++)
	{
		int row, collumn;
		srand((int)time(0));
		while (true)
		{
			row = rand() % SUITS;
			collumn = rand() % FACES;
			if (deck[row][collumn] == 0)
				break;
		}
		deck[row][collumn] = i;
	}

}

void printCardsShuffling(int deck[][FACES], const char* suits[], const char* faces[])
{
	for (int card = 0; card < 52; card++)
	{
		for (int i = 0; i < SUITS; i++)
		{
			for (int j = 0; j < FACES; j++)
			{
				if (deck[i][j] == card)
					cout << "(" << suits[i] << ", " << faces[j] << ")" << endl;
			}
		}
	}
}

int** dealingForHand(int deck[SUITS][FACES]) 
{
	int** a = new int *[5];
	for (int i = 0; i < 5; i++) 
	{
		a[i] = new int[2];
	}
	for (int card = 0; card < 5; card++) 
	{
		for (int i = 0; i < SUITS; i++) 
		{
			for (int j = 0; j < FACES; j++) 
			if (card == deck[i][j])
			{
				a[card][0] = i;
				a[card][1] = j;
			}
		}
	}
	return a;
}

void printHand(int** hand, const char* suits[],const char* faces[])
{
	for (int i = 0; i < 5; i++)
	{
		cout << "(" << suits[hand[i][0]] << "," << faces[hand[i][1]] << ")" << endl;
	}
}

void Sort(int** hand) 
{
	for (int i = 0; i < 5; i++) {
		for (int j = i + 1; j < 5; j++) {
			if (hand[i][1] > hand[j][1]) {
				swap(hand[i][1], hand[j][1]);
				swap(hand[i][0], hand[j][0]);
			}
		}
	}
}

int Flush(int** hand) 
{
	Sort(hand);
	for (int i = 0; i < 4; i++)
	if (hand[i][0] != hand[i + 1][0]) 
		return 0;
	return 1;
}

int Straight(int** hand) 
{
	Sort(hand);
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < i + 1; j++) {

		}
	}
	for (int i = 0; i < 4; i++) {
		if (abs(hand[i + 1][1]) - abs(hand[i][1] != 1)) return 0;
	}
	return 1;
}

int Straightflush(int** hand) 
{
	Sort(hand);
	if (Flush(hand) && Straight(hand)) return 1;
	return 0;
}

int isFourOfAKind(int** hand)
{
	Sort(hand);
	int count = 0;
	for (int i = 0; i < 5; i++) {
		if (hand[i][1] == hand[i + 1][1]) count++;
	}
	if (count == 3) return 1;
}

int isThreeOfAKind(int** hand)
{
	int CheckMang[5];
	int m = 0;
	for (int i = 0; i < 5; i++)
		CheckMang[m++] = hand[i][0];
	int b[14] = { 0 };
	for (int i = 0; i < 5; i++)
	{
		b[CheckMang[i]] += 1;
	}
	int Triple = 0;
	int Double = 0;
	for (int i = 1; i < 14; i++)
	{
		if (b[i] == 3)
			Triple++;
		if (b[i] == 2)
			Double++;
	}
	if (Triple == 1 && Double == 0)
		return 1;
	return 0;
}

int isTwoPairs(int** hand) 
{
	int CheckMang[5];
	int m = 0;
	for (int i = 0; i < 5; i++)
		CheckMang[m++] = hand[i][0];
	int b[14] = { 0 };
	for (int i = 0; i < 5; i++)
	{
		b[CheckMang[i]] += 1;
	}
	int Triple = 0;
	int Double = 0;
	for (int i = 1; i < 14; i++)
	{
		if (b[i] == 3)
			Triple++;
		if (b[i] == 2)
			Double++;
	}
	if (Triple == 0 && Double == 2)
		return 1;
	return 0;
}

int isPair(int** hand) 
{
	int CheckMang[5];
	int m = 0;
	for (int i = 0; i < 5; i++)
		CheckMang[m++] = hand[i][0];
	int b[14] = { 0 };
	for (int i = 0; i < 5; i++)
	{
		b[CheckMang[i]] += 1;
	}
	int Triple = 0;
	int Double = 0;
	for (int i = 1; i < 14; i++)
	{
		if (b[i] == 3)
			Triple++;
		if (b[i] == 2)
			Double++;
	}
	if (Triple == 0 && Double == 1)
		return 1;
	return 0;
}


/*
int getHighestCard(int** hand)
{

}
*/

int main()
{
	int deck[SUITS][FACES];
	int** hand = new int*[];
	shuffleCards(deck);
	printCardsShuffling(deck, suits, faces);
	hand = dealingForHand(deck);
	cout << "\n 5 la bai tren tay nguoi choi la: " << endl;
	printHand(hand, suits, faces);
	if (Flush(hand))
		cout << " Nguyen cai thung lun";
	if (Straight(hand))
		cout << " Nguyen cai Sanh lun , vl";
	if (Straightflush(hand))
		cout << " Vc Thung pha sanh?!??";
	if (isFourOfAKind(hand))
		cout << " Nguyen cai tu quy luon";
	if (isThreeOfAKind(hand))
		cout << " Sam co";
	if (isTwoPairs(hand))
		cout << " Hai doi";
	if (isPair(hand))
		cout << " Mot doi";
	delete[] hand;
	_getch();
}

