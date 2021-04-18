#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h>

#define SUITS 4
#define FACES 13

using namespace std;

const char* suits[SUITS] = { "Hearts", "Diamonds", "Clubs", "Spades" };
const char* faces[FACES] = { "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A" };

// Lenh xao bai
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

// Xuat bai xao duoc
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
	for (int i = 0; i < SUITS; i++)
	{
		for (int j = 0; j < FACES; j++)
		{
			cout << deck[i][j] << " ";
		}
		cout << endl;
	}
}

// 1. Poker cho 1 nguoi choi:
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

// In bai tren tay nguoi choi
void printHand(int** hand, const char* suits[], const char* faces[])
{
	for (int i = 0; i < 5; i++)
	{
		cout << "(" << suits[hand[i][0]] << " , " << faces[hand[i][1]] << ")" << endl;
	}
}

// Phan loai bai de xet cac gia tri bai tren tay
void Sort(int** &hand)
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

// Xet Sanh (  5 quan bai lien tiep , khong dong chat )
int isStraight(int** hand){
	if (hand[4][1] == 12 && hand[0][1] == 9)
	{
		for (int i = 1; i < 5; i++)
		{
			if (hand[i][1] != hand[i + 1][1] - 1)
			{
				return 0;
			}
		}

	}
	else{
		for (int i = 0; i < 4; i++)
		{
			if (hand[i][1] != hand[i + 1][1] - 1)
			{
				return 0;
			}
		}
	}
	return 4;
}

// Xet Thung ( 5 quan bai dong chat, khong lien tiep )
int isFlush(int** hand) {
	Sort(hand);
	for (int i = 0; i < 4; i++)
	if (hand[i][0] != hand[i + 1][0]) return 0;
	return 5;
}

// Xet Thung Pha Sanh ( 5 quan bai lien tiep , dong chat )
int isStraightFlush(int** hand){
	if (isStraight(hand) != 0 && isFlush(hand) != 0)
	{
		return 8;
	}
	return 0;
}

// Xet Tu quy ( 4 Con bai cung So )
int isFourOfAKind(int** hand) {
	Sort(hand);
	int count = 0;
	for (int i = 0; i < 4; i++) {
		if (hand[i][1] == hand[i + 1][1]) count++;
	}
	for (int i = 0; i < 3; i++) {
		if (hand[i][1] == hand[i + 1][1] && hand[i][1] == hand[i + 2][1]) count++;
	}
	if (count == 5) return 7;
	else return 0;
}

// Xet Cu Lu ( 1 Pair va 1 Three of a kind )
int isFullhouse(int** hand)
{
	int b[14] = { 0 };
	for (int i = 0; i < 5; i++)
	{
		b[hand[i][1]] += 1;
	}
	int triple = 0;
	int pair = 0;
	for (int i = 1; i < 14; i++)
	{
		if (b[i] == 3)
			triple++;
		if (b[i] == 2)
			pair++;
	}
	if (triple == 1 && pair == 1)
		return 6;
	return 0;
}

// Xet Sam Co ( 3 con giong nhau )
int isThreeOfAKind(int** hand)
{
	Sort(hand);
	int count = 0;
	for (int i = 0; i < 4; i++) {
		if (hand[i][1] == hand[i + 1][1]) count++;
	}
	for (int i = 0; i < 3; i++) {
		if (hand[i][1] == hand[i + 1][1] && hand[i][1] == hand[i + 2][1]) count++;
	}
	if (count == 3) return 3;
	else return 0;
}

// Xet 2 Doi 
int isTwoPairs(int** hand) {
	Sort(hand);
	int count = 0;
	for (int i = 0; i < 4; i++) {
		if (hand[i][1] == hand[i + 1][1]) count++;
	}
	for (int i = 0; i < 3; i++) {
		if (hand[i][1] == hand[i + 1][1] && hand[i][1] == hand[i + 2][1]) count++;
	}
	if (count == 2) return 2;
    return 0;
}

// Xet doi ( 2 con giong nhau)
int isPair(int** hand) {
	Sort(hand);
	int count = 0;
	for (int i = 0; i < 4; i++) {
		if (hand[i][1] == hand[i + 1][1]) count++;
	}
	if (count == 1) return 1;
	 return 0;
}

// Xet bai cao nhat ( chi trong truong hop bai trong tay khong roi vao nhung truong hop bai con lai ) 
int getHighestCard(int** hand)
{
	Sort(hand);
	int count = 0;
	int max = -9999;
	int i = 0;
	for (; i < 5; i++)
	{
		for (int j = i + 1; j < 5; j++) {
			if (hand[i][1] < hand[j][1])
				max = j;
			else if (hand[i][1] = hand[j][1])
				count++;
		}
	}
	if (count == 4) cout << "You have a highest card";
	return max;
}

int** createHandTest(int deck[SUITS][FACES], int a[]){
	int** r = new int *[5];
	for (int i = 0; i < 5; i++)
	{
		r[i] = new int[2];
	}
	cout << "\n   Input cards to check as you wish: " << endl;
	for (int card = 0; card < 5; card++)
	{
		cout << " Card[" << card << "]: ";
		cin >> a[card];
		for (int i = 0; i < SUITS; i++)
		{
			for (int j = 0; j < FACES; j++)
			{
				if (a[card] == deck[i][j])
				{
					r[card][0] = i;
					r[card][1] = j;
				}
			}
		}
		
	}
	printHand(r, suits, faces);
	if (isFlush(r))
		cout << " You have a Flush ";
	if (isStraight(r))
		cout << " You have a Straight";
	if (isStraightFlush(r))
		cout << " You Have a Straight of Flush !!! Impressive !!!";
	if (isFourOfAKind(r))
		cout << " You Have a Four of a Kind !!! Amazing !!!";
	if (isThreeOfAKind(r))
		cout << " You Have a Three Of A Kind ";
	if (isTwoPairs(r))
		cout << " You Have Two Pairs";
	if (isPair(r))
		cout << " You Have a Pair";
	if (getHighestCard(r))
		cout << " You Have a Highest Card";
	return r;
}

// 2. Poker for 2 ( or N ) Players:
int** dealingForHand(int deck[SUITS][FACES], int order, int n)
{
	int** player = new int*[5];
	int card = order;
	for (int i = 0; i < 5; i++) {
		player[i] = new int[2];
	}
	int a = 0;
	while (card < 5 * n){
		for (int i = 0; i < 4; i++){
			for (int j = 0; j < 13; j++)
			if (card == deck[i][j]){
				player[a][0] = i;
				player[a][1] = j;
				card += n;
				a++;
				if (card >= 5 * n) break;
			}
			if (card >= 5 * n) break;
		}
	}
	return player;
}

int getStatusOfHand(int** hand) {
	int score;
	if (isStraightFlush(hand)) score = 8;
	if (isFourOfAKind(hand)) score = 7;
	if (isFullhouse(hand)) score = 6;
	if (isFlush(hand)) score = 5;
	if (isStraight(hand)) score = 4;
	if (isThreeOfAKind(hand)) score = 3;
	if (isTwoPairs(hand)) score = 2;
	if (isPair(hand)) score = 1;
	else score = 0;
	return score;
}

int*** dealingForHands(int deck[][13], int &n){
	cout << " \n\n----- N Players Mode: ----- ";
	do {
		cout << "\n  Input the number of player(s): ";
		cin >> n;
	} while (n <= 2 || n > 10);
	int*** player = new int**[n];
	shuffleCards(deck);
	for (int i = 0; i < n; i++) {
		player[i] = dealingForHand(deck, i, n);
		printHand(player[i], suits, faces);
		cout << "Score: " << getStatusOfHand(player[i]) << endl << "---------" << endl;
	}
	return player;
}


int* rankingHands(int*** hands, int n) {
	int* a = new int;
	int* b = new int;
	int max = 999999;
	for (int i = 0; i < n; i++) {
		int max2 = 0;
		for (int j = i + 1; j < n; j++) {
			if (getStatusOfHand(hands[i]) < getStatusOfHand(hands[j]) && max2 < max) {
				max2 = j;
			}
			else max2 = i;
		}
		a[max2] = i;
		max2 = max;
	}
	return a;
}

/*
void Menu()
{
	int n;
	int deck[SUITS][FACES];
	do {
		cout << "---------- WELCOME TO POKER WORLD ---------- " << endl;
		cout << "--------- By Huu Bang and Khanh Duy -------- " << endl;
		cout << "  1/ Test Cards " << endl;
		cout << "  2/ Single Player  " << endl;
		cout << "  3/ Multiplayer  " << endl;
		cout << "  4/ Playing with Dealer " << endl;
		cout << "      Please choose a mode to play " << endl;
		cin >> n;
		switch (n)
		{
		case 0: break;
		case 1:  
			do
			{
				system("cls");
				cout << "---------- WELCOME TO POKER WORLD ---------- " << endl;
				cout << "--------- By Huu Bang and Khanh Duy -------- " << endl;
				printCardsShuffling(deck, suits, faces) << endl;	break;
				cout << " Wanna Try again? (y/n)" << endl;
				cin  >> y;
			} while ( y == 'y');
			break;

		case 2:
		do
		{
			system("cls");
			cout << "---------- WELCOME TO POKER WORLD ---------- " << endl;
			cout << "--------- By Huu Bang and Khanh Duy -------- " << endl;
			cout << "\t\t\t\t\t (1) Play Solo" << endl;
			cout << "\t\t\t\t\t (2) Play against Dealer" << endl;
			int 

		default: {
				 cout << " Your Input number is invalid , Try again please !!!" << endl;	break;
				 }
		}
	} while (n); // n != 0;
}


int* evaluateHands(int po[], int n, int *&a)
{
	for (int i = 0; i < n; i++)
		a[i] += po[i];
	return a;
}

int checkbai(int Player[8], int n)
{
	int max = 0, a[5];
	for (int i1 = 0; i1<n - 5 + 1; i1++)
	for (int i2 = i1 + 1; i2<n - 5 + 2; i2++)
	for (int i3 = i2 + 1; i3<n - 5 + 3; i3++)
	for (int i4 = i3 + 1; i4<n - 5 + 4; i4++)
	for (int i5 = i4 + 1; i5 < n - 5 + 5; i5++)
	{
		a[0] = Player[i1]; a[1] = Player[i2]; a[2] = Player[i3]; a[3] = Player[i4]; a[4] = Player[i5];
		if (max < getStatusOfHand(a)) max = getStatusOfHand(a);
	}
	return max;
}



void dealer(int deck[SUITS][FACES], int Dealer[8], int Player[5][8], int n, int level)
{
	int nP = 5, nD = 5;
	if (level == 1) nP = 8;
	else if (level == 3) nD = 8;
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = 0; j < nP; j++)
			Player[i][j] = a[i + j * n].P;
		po[i] = checkbai(Player[i], nP);
	}

	for (int i = 0; i < nD; i++)
		Dealer[i] = a[n - 1 + i * n].P;
	po[n - 1] = checkbai(Dealer, nD);

	int c[10];
	for (int i = 0; i < n; i++)
		c[i] = i + 1;

	for (int i = 0; i < n; i++)
	{
		if (i != n - 1)
		{
			cout << "Player " << i + 1 << endl;
			for (int j = 0; j < nP; j++)
				cout << a[i + j * n].s << " ";
			cout << endl;
			cout << "point : " << po[c[i] - 1] << endl << endl;
		}
		else
		{
			cout << "Dealer " << endl;
			for (int j = 0; j < nD; j++)
				cout << a[i + j * n].s << " ";
			cout << endl;
			cout << "point : " << po[i] << endl << endl;
		}
	}

	for (int i = 0; i < n - 1; i++)
	for (int j = i + 1; j < n; j++)
	{
		if (po[i] < po[j])
		{
			swap(po[i], po[j]);
			swap(c[i], c[j]);
		}
	}

	if (po[n - 1] == po[0]) cout << "===== Tie! =====" << endl;
	else
	{
		cout << "===== The Winner =====" << endl;

		for (int i = 0; i < n; i++)
		if (po[i] == po[0])
		if (c[i] == n) cout << "- Dealer" << endl;
		else cout << "- Player " << c[i] << endl;

	}
	cout << endl;
}
*/
int main()
{
	int deck[SUITS][FACES],a[1000];
	int** hand = NULL;
	int*** hands = NULL;
	int** r = NULL;
	//Menu();
	shuffleCards(deck);
	printCardsShuffling(deck, suits, faces);
	r = createHandTest(deck, a); 
	hand = dealingForHand(deck);
	cout << " \n ----- 1 Player Mode: ----- ";
	cout << " \n  5 la bai tren tay nguoi choi la: " << endl;
	printHand(hand, suits, faces);
		if (isFlush(hand))
			cout << " You have a Flush ";
		if (isStraight(hand))
			cout << " You have a Straight";
		if (isStraightFlush(hand))
			cout << " You Have a Straight of Flush !!! Impressive !!!";
		if (isFourOfAKind(hand))
			cout << " You Have a Four of a Kind !!! Amazing !!!";
		if (isFullhouse(hand))
			cout << " You have a Fullhouse !!! What a beast !";
		if (isThreeOfAKind(hand))
			cout << " You Have a Three Of A Kind ";
		if (isTwoPairs(hand))
			cout << " You Have Two Pairs";
		if (isPair(hand))
			cout << " You Have a Pair";
		if (getHighestCard(hand))
			cout << " You Have a Highest Card";
		if (getStatusOfHand(hand) == 0)
		{
			cout << "\n Player's Highest Card is: " << getHighestCard(hand) << endl;
		}
	int n, po[1000];
	//int *a = new int;
	dealingForHands(deck, n);
	hands = dealingForHands(deck, n);
	rankingHands(hands, n);
	//evaluateHands(po, n,a);
	delete[] hand;
	//delete[] * &a;
	_getch();
}
