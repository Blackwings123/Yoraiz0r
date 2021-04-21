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

//												 1. Poker cho 1 nguoi choi:
// Ham de chia bai den nguoi choi
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
	Sort(hand);
	int count = 0;
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
	Sort(hand);
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
int isFullhouse(int** hand) {
	Sort(hand);
	int count = 0;
	for (int i = 0; i < 4; i++) {
		if (hand[i][1] == hand[i + 1][1]) count++;
	}
	for (int i = 0; i < 3; i++) {
		if (hand[i][1] == hand[i + 1][1] && hand[i][1] == hand[i + 2][1]) count++;
	}
	if (count == 4) return 6;
	else return 0;
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
	if (count == 2 && !(isFullhouse(hand))) return 2;
	else return 0;
}

// Xet doi ( 2 con giong nhau)
int isPair(int** hand) {
	Sort(hand);
	int count = 0;
	for (int i = 0; i < 4; i++) {
		if (hand[i][1] == hand[i + 1][1]) count++;
	}
	if (count == 1) return 1;
	else return 0;
}

// Xet bai cao nhat ( chi trong truong hop bai trong tay khong roi vao nhung truong hop bai con lai ) 
int getHighestCard(int** hand)
{
	Sort(hand);
	char max = 0;
	int res;
	for (int i = 0; i < 5; i++)
	{
		for (int j = i + 1; j < 5; j++) {
			if (hand[i][1] < hand[j][1] && hand[j][1] > max)
				max = hand[j][1];
		}
	}
	for (int i = 0; i<5; i++){
		if (hand[i][1] == max){
			res = i;
			break;
		}
	}
	if (max == 0) return max = '2';
	if (max == 1) return max = '3';
	if (max == 2) return max = '4';
	if (max == 3) return max = '5';
	if (max == 4) return max = '6';
	if (max == 5) return max = '7';
	if (max == 6) return max = '8';
	if (max == 7) return max = '9';
	if (max == 8) return max = '10';
	if (max == 9) return max = 'J';
	if (max == 10)return max = 'Q';
	if (max == 11)return max = 'K';
	if (max == 12)return max = 'A';
	return max;
}

// Ham de kiem tra bai duoc nguoi dung truc tiep nhap vao
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
	if (isStraightFlush(r))
	{
		cout << " You Have a Straight of Flush !!! Impressive !!!";
	}else if (isFlush(r))
	{
		cout << " You have a Flush ";
	}
	else if (isStraight(r))
	{
		cout << " You have a Straight";
	}else if (isFullhouse(r))
	{
		cout << " You have a Fullhouse !!! What a beast !";
	}
	if (isFourOfAKind(r))
	{
		cout << " You Have a Four of a Kind !!! Amazing !!!";
	}else
	if (isThreeOfAKind(r))
	{
		cout << " You Have a Three Of A Kind ";
	}else
	if (isTwoPairs(r))
	{
		cout << " You Have Two Pairs";
	}else
	if (isPair(r))
		cout << " You Have a Pair";

	return r;
}

//                                                 2. Poker for 2 ( or N ) Players:
// Ham de chia bai den N nguoi choi ( Cau 2A ):
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

// Cau 2B:
int getStatusOfHand(int** hand) {
	int score;
	if (isStraightFlush(hand))
	{
		score = 8;
	}
	else if (isFourOfAKind(hand))
	{
		score = 7;
	}
	else if (isFullhouse(hand))
	{
		score = 6;
	}
	else if (isFlush(hand))
	{
		score = 5;
	}
	else if (isStraight(hand))
	{
		score = 4;
	}
	else if (isThreeOfAKind(hand))
	{
		score = 3;
	}
	else if (isTwoPairs(hand))
	{
		score = 2;
	}
	else if (isPair(hand))
	{
		score = 1;
	}
	else score = 0;
	return score;
}

// Cau 2A:
int*** dealingForHands(int deck[][13], int &n){

	cout << " \n\n -------------------------------------------------- N Players Mode:  -------------------------------------------------- ";
	do {
		cout << "\n  Input the number of player(s): ";
		cin >> n;
	} while (n <= 1 || n > 10);
	int*** player = new int**[n];
	shuffleCards(deck);
	for (int i = 0; i < n; i++) {
		player[i] = dealingForHand(deck, i, n);
		cout << " - Player: " << i + 1 << endl;
		printHand(player[i], suits, faces);

		cout << " - The Score is: " << getStatusOfHand(player[i]) << endl << "-------------------------" << endl;
	}
	return player;
}

// Xep hang bai tren tay N nguoi choi ( 2C )
int* rankingHands(int*** hands, int n)
{
	int score[10];
	int card[10];
	int* result = new int[n];
	int rank = 1;
	for (int i = 0; i < n; i++){
		score[i] = getStatusOfHand(hands[i]);
		card[i] = getHighestCard(hands[i]);
	}


	int count = 0;
	while (count != n)
	{
		int max = -999;
		for (int i = 0; i < n; i++)
		if (score[i] > max)
			max = score[i];

		if (max != 0)
		{
			for (int i = 0; i < n; i++)
			if (score[i] == max)
			{
				result[i] = rank;
				score[i] = -99;
				count++;
			}
			rank++;
		}
		else
		{
			int maxCard = -999;
			for (int i = 0; i < n; i++)
			if ((getStatusOfHand(hands[i]) == 0) && (card[i] > maxCard))
				maxCard = card[i];

			for (int i = 0; i < n; i++)
			if ((getStatusOfHand(hands[i]) == 0) && (card[i] == maxCard))
			{
				result[i] = rank;
				card[i] = -99;
				score[i] = -99;
				count++;
			}
			rank++;
		}
	}

	return result;
}

/*
int** handOfHands(int*** hands, int n)
{
	int** hand = new int*[5];
	for (int i = 0; i < 5; i++)
		hand[i] = new int[2];
	for (int j = 0; j < 5; j++) {
		hand[j][0] = hands[n][j][0];
		hand[j][1] = hands[n][j][1];
	}
	return hand;
}

void printHand2(int*** hand, const char* suits[], const char* faces[], int n)
{
	int** hand1, a, b;
	for (int i = 0; i < n; i++) {
		cout << "\nCards of Player[" << i + 1 << "]:\n";
		for (int j = 0; j < 5; j++) {
			cout << faces[hand[i][j][1]] << suits[hand[i][j][0]] << "\t";
		}
		hand1 = handOfHands(hand, i);
		check(hand1, suits, faces);
		cout << endl;
	}
}

void evaluateHands(int deck[SUITS][FACES], const char* suits[], const char* faces[], int n, int m)
{
	int* a = new int[n];
	int* b = new int[n];
	int** hand1, *hand2;
	int max = 11, index;
	for (int i = 0; i < n; i++) {
		b[i] = 0;
	}

	shuffleCards(deck);
	for (int i = 0; i < m; i++) {
		hand2 = dealingForHands(deck, n);
		cout << "\nPhase " << i + 1 << ":";
		printHand2(hand2, suits, faces, n);
		for (int j = 0; j < n; j++) {
			hand1 = handOfHands(hand2, j);
			b[j] += getStatusOfHand(hand1);

		}
		shuffleCards(deck);

	}
	for (int i = 0; i < n; i++) {
		a[i] = b[i];
	}
	for (int i = 0; i < n - 1; i++) {
		for (int j = i + 1; j < n; j++) {
			if (b[i] < b[j]) {
				swap(b[j], b[i]);
			}
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (a[i] == b[j]) {
				a[i] = j + 1;
				break;
			}
		}
	}
	cout << "\n\n Rank:";
	for (int i = 0; i < n; i++) {
		cout << "\nPlayer" << i + 1 << ": ";
		cout << a[i];
	}
	cout << endl;
	for (int i = 0; i < n; i++) {
		if (a[i] < max) {
			max = a[i];
			index = i;	
		}
	}
	cout << "\n Congratulate Player" << index + 1 << "!";
	for (int i = 0; i < n; i++) {
		if (a[i] == max && i != index) {
			cout << " & Player" << i + 1;
		}
	}
	cout << endl;
}
*/

int main()
{
	int** hand = NULL;
	int*** hands = NULL;
	int** r = NULL;
	int n, selection,a[1000];
	int deck[SUITS][FACES];
	do {
		cout << "\n                                      ---------- WELCOME TO POKER WORLD ---------- " << endl;
		cout << "\n                                      --------- By Huu Bang and Khanh Duy -------- " << endl;
		cout << "\n                                                 1/ Test Cards " << endl;
		cout << "                                                 2/ Single Player  " << endl;
		cout << "                                                 3/ Multiplayer  " << endl;
		cout << "                                                 4/ Playing with Dealer " << endl;
		cout << "\n                                              Please choose a mode to play: " ;
		cin >> selection;
	} while (selection <= 1 && selection >= 5);
	while ((selection >= 1 && selection <= 1000))
	{
		cout << endl;
		if (selection == 1)
		{
			system("cls");
			shuffleCards(deck);
			printCardsShuffling(deck, suits, faces);
			r = createHandTest(deck, a);

		}
		cout << endl;
		if (selection == 2)
		{
			system("cls");
			cout << "\n                                   SINGLE PLAYER MODE:" <<endl;
			shuffleCards(deck);
			printCardsShuffling(deck, suits, faces);
			hand = dealingForHand(deck);
			cout << " \n\n -------------------------------------------------- 1 Player Mode: -------------------------------------------------- ";
			cout << " \n  5 la bai tren tay nguoi choi la: " << endl;
			printHand(hand, suits, faces);
			if (isStraightFlush(hand))
			{
				cout << " You Have a Straight of Flush !!! Impressive !!!";
			}
			else if (isFlush(hand))
			{
				cout << " You have a Flush ";
			}
			else if (isStraight(hand))
			{
				cout << " You have a Straight";
			}
			else if (isFourOfAKind(hand))
			{
				cout << " You Have a Four of a Kind !!! Amazing !!!";
			}
			else if (isFullhouse(hand))
			{
				cout << " You have a Fullhouse !!! What a beast !";
			}
			else if (isThreeOfAKind(hand))
			{
				cout << " You Have a Three Of A Kind ";
			}
			else if (isTwoPairs(hand))
			{
				cout << " You Have Two Pairs";
			}
			else if (isPair(hand))
			{
				cout << " You Have a Pair";
			}
			char highestcard = getHighestCard(hand);
			if (getHighestCard(hand))
			{
				cout << "\n Player's Highest card is: " << highestcard << endl;
			}

		}

		if (selection == 3)
		{
			system("cls");
			hands = dealingForHands(deck, n);
			int* rank = rankingHands(hands, n);
			for (int i = 0; i < n; i++){
				cout << "Player " << i + 1 << "'s rank is: " << *(rank + i) << endl;
			}
		}

		if (selection == 4)
		{
			system("cls");
			shuffleCards(deck);
			printCardsShuffling(deck, suits, faces);
			hand = dealingForHand(deck);
			cout << " \n\n -------------------------------------------------- Dealer Mode: -------------------------------------------------- ";
			cout << " \n  5 la bai luc dau tren tay Dealer la: " << endl;
			printHand(hand, suits, faces);
			if (isStraightFlush(hand))
			{
				cout << " The Dealer's first hand has a Straight of Flush !!! Impressive !!!";
			}
			else if (isFlush(hand))
			{
				cout << " The Dealer's first hand has a Flush ";
			}
			else if (isStraight(hand))
			{
				cout << " The Dealer's first hand has a Straight";
			}
			else if (isFourOfAKind(hand))
			{
				cout << " The Dealer's first hand has a Four of a Kind !!! Amazing !!!";
			}
			else if (isFullhouse(hand))
			{
				cout << " The Dealer's first hand has a Fullhouse !!! What a beast !";
			}
			else if (isThreeOfAKind(hand))
			{
				cout << " The Dealer's first hand has a Three Of A Kind ";
			}
			else if (isTwoPairs(hand))
			{
				cout << " The Dealer's first hand has Two Pairs";
			}
			else if (isPair(hand))
			{
				cout << " The Dealer's first hand has a Pair";
			}
			char highestcard = getHighestCard(hand);
			if (getHighestCard(hand))
			{
				cout << "\n The Dealer's Highest card: " << highestcard << endl;
			}
		}
		cout << "                                                  Try Another one : ";
		cin >> selection;
		cout << endl;
	}

	//evaluateHands(po, n,a);
	delete[] hand;
	_getch();
}
