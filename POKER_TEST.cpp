#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <Windows.h>

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
	}
	else if (isFlush(r))
	{
		cout << " You have a Flush ";
	}
	else if (isStraight(r))
	{
		cout << " You have a Straight";
	}
	else if (isFullhouse(r))
	{
		cout << " You have a Fullhouse !!! What a beast !";
	}
	if (isFourOfAKind(r))
	{
		cout << " You Have a Four of a Kind !!! Amazing !!!";
	}
	else
	if (isThreeOfAKind(r))
	{
		cout << " You Have a Three Of A Kind ";
	}
	else
	if (isTwoPairs(r))
	{
		cout << " You Have Two Pairs";
	}
	else
	if (isPair(r))
		cout << " You Have a Pair";

	return r;
}

// Hàm d? xét tru?ng h?p bài trên tay c?a 1 ngu?i choi
void CheckHand(int** hand)
{
	Sort(hand);
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

//                                                 2. Poker for 2 ( or N ) Players:

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

// Ham de chia bai den N nguoi choi  (Cau 2A):
int*** dealingForHands(int deck[][13], int& n) {
	int*** player = new int**[n];
	for (int i = 0; i < n; i++) {
		player[i] = dealingForHand(deck, i, n);
	}
	return player;
}

// Xep hang bai tren tay N nguoi choi ( câu 2C )
int* rankingHands(int*** hands, int n)
{
	int* score = new int[n];
	int* res = new int[n];
	int rank = 1;
	for (int i = 0; i < n; i++){
		score[i] = getStatusOfHand(hands[i]);
	}

	int count = 0;
	while (count != n) {
		int max = 0;
		for (int i = 0; i < n; i++) {
			if (score[i] > max)
				max = score[i];
		}

		if (max != 0) {
			for (int i = 0; i < n; i++)
			if (score[i] == max) {
				res[i] = rank;
				score[i] = -99;
				count++;
			}
			rank++;
		}
		else {
			for (int i = 0; i < n; i++)
			if ((getStatusOfHand(hands[i]) == 0)) {
				res[i] = rank;
				score[i] = -99;
				count++;
			}
			rank++;
		}
	}
	return res;
}

// Tinh tong diem cua N nguoi choi sau S vong :
int* evaluateHands(int*** &hands, int n, int turn, int deck[4][13])
{
	int *sum = new int[n];
	for (int i = 0; i < n; i++) {
		sum[i] = 0;
	}
	for (int i = 0; i < turn; i++) {
		shuffleCards(deck);
		Sleep(1000);
		hands = dealingForHands(deck, n);
		for (int j = 0; j < n; j++) {
			cout << "Turn " << i + 1 << endl;
			cout << "Player " << j + 1 << endl << "----===----" << endl;
			printHand(hands[j], suits, faces); cout << endl;
			cout << "Score: " << getStatusOfHand(hands[j]) << endl;
			cout << " ________  " << endl;
			sum[j] += getStatusOfHand(hands[j]);
		}
	}	
	return sum;
}

// Ham xao bai va in bai gop chung
void shuffleandprint(int deck[][13]) {
	shuffleCards(deck);
	printCardsShuffling(deck, suits, faces);
}

// Ham xet bai tren tay va Hang ( Rankings) cua che do N player ( Trong 1 Round dau duy nhat )
void np(int*** hands, int deck[][13], int &n) {
	shuffleandprint(deck);
	cout << " \n\n -------------------------------------------------- N Players Mode: -------------------------------------------------- ";
	do {
		cout << "\n  Input the number of player(s):";
		cin >> n;
		cout << "______________\n";
	} while (n <= 2 || n > 10);
	hands = dealingForHands(deck, n);
	//np(hands, deck, n);
	for (int i = 0; i < n; i++) {
		printHand(hands[i], suits, faces);
		if (isFlush(hands[i])) {
			cout << " You have a Flush \n";
			cout << "Score: " << getStatusOfHand(hands[i]) << endl << "---------" << endl << endl << "_______" << endl;
		}
		else if (isStraight(hands[i])) {
			cout << " You have a Straight\n";
			cout << "Score: " << getStatusOfHand(hands[i]) << endl << "---------" << endl << endl << "_______" << endl;
		}
		else if (isStraightFlush(hands[i])) {
			cout << " You Have a Straight of Flush !!! Impressive !!!\n";
			cout << "Score: " << getStatusOfHand(hands[i]) << endl << "---------" << endl << endl << "_______" << endl;
		}
		else if (isFourOfAKind(hands[i])) {
			cout << " You Have a Four of a Kind !!! Amazing !!!\n";
			cout << "Score: " << getStatusOfHand(hands[i]) << endl << "---------" << endl << endl << "_______" << endl;
		}
		else if (isFullhouse(hands[i])) {
			cout << " You have a Fullhouse !!! What a beast !\n";
			cout << "Score: " << getStatusOfHand(hands[i]) << endl << "---------" << endl << endl << "_______" << endl;
		}
		else if (isThreeOfAKind(hands[i])) {
			cout << " You Have a Three Of A Kind \n";
			cout << "Score: " << getStatusOfHand(hands[i]) << endl << "---------" << endl << endl << "_______" << endl;
		}
		else if (isTwoPairs(hands[i])) {
			cout << " You Have Two Pairs\n";
			cout << "Score: " << getStatusOfHand(hands[i]) << endl << "---------" << endl << endl << "_______" << endl;
		}
		else if (isPair(hands[i])) {
			cout << " You Have a Pair\n";
			cout << "Score: " << getStatusOfHand(hands[i]) << endl << "---------" << endl << endl << "_______" << endl;
		}
		else {
			char highestcards = getHighestCard(hands[i]);
			cout << "\n Highest card is the " << highestcards << " card!!";
			cout << "\n Score: " << getStatusOfHand(hands[i]) << endl << "---------" << endl;
		}
	}
	int* rank = rankingHands(hands, n);
	for (int i = 0; i < n; i++) {
		cout << " The rank of player " << i + 1 << " is:" << *(rank + i) << endl;
	}
}

// Ham xet bai tren tay va Hang ( Rankings) cua che do N player ( Trong N Round d?u)
void np2(int*** hands, int deck[][13], int& n) {
	shuffleCards(deck);
	//shuffleandprint(deck);
	cout << " \n\n -------------------------------------------------- N Players Mode: -------------------------------------------------- ";
	do {
		cout << "\n  Input the number of player(s):";
		cin >> n;
		cout << "______________\n";
	} while (n > 10);
	hands = dealingForHands(deck, n);
	for (int i = 0; i < n; i++) {
		printHand(hands[i], suits, faces);
		if (isFlush(hands[i])) {
			cout << " You have a Flush \n";
			cout << "Score: " << getStatusOfHand(hands[i]) << endl << "---------" << endl << endl << "_______" << endl;
		}
		else if (isStraight(hands[i])) {
			cout << " You have a Straight\n";
			cout << "Score: " << getStatusOfHand(hands[i]) << endl << "---------" << endl << endl << "_______" << endl;
		}
		else if (isStraightFlush(hands[i])) {
			cout << " You Have a Straight of Flush !!! Impressive !!!\n";
			cout << "Score: " << getStatusOfHand(hands[i]) << endl << "---------" << endl << endl << "_______" << endl;
		}
		else if (isFourOfAKind(hands[i])) {
			cout << " You Have a Four of a Kind !!! Amazing !!!\n";
			cout << "Score: " << getStatusOfHand(hands[i]) << endl << "---------" << endl << endl << "_______" << endl;
		}
		else if (isFullhouse(hands[i])) {
			cout << " You have a Fullhouse !!! What a beast !\n";
			cout << "Score: " << getStatusOfHand(hands[i]) << endl << "---------" << endl << endl << "_______" << endl;
		}
		else if (isThreeOfAKind(hands[i])) {
			cout << " You Have a Three Of A Kind \n";
			cout << "Score: " << getStatusOfHand(hands[i]) << endl << "---------" << endl << endl << "_______" << endl;
		}
		else if (isTwoPairs(hands[i])) {
			cout << " You Have Two Pairs\n";
			cout << "Score: " << getStatusOfHand(hands[i]) << endl << "---------" << endl << endl << "_______" << endl;
		}
		else if (isPair(hands[i])) {
			cout << " You Have a Pair\n";
			cout << "Score: " << getStatusOfHand(hands[i]) << endl << "---------" << endl << endl << "_______" << endl;
		}
		else {
			char highestcards = getHighestCard(hands[i]);
			cout << "\n Highest card is the " << highestcards << " card!!" << endl;
			cout << "Score: " << getStatusOfHand(hands[i]) << endl << "---------" << endl;
		}
	}
	int* rank = rankingHands(hands, n);
	int ranked;
	for (int i = 0; i < n; i++) {
		cout << "The rank of player " << i + 1 << " is:" << *(rank + i) << endl;
	}
	cout << "___________\n";
	int turn;
	cout << "Input turn:";
	cin >> turn;
	cout << "_________\n";
	int* sum = evaluateHands(hands, n, turn, deck);
	for (int i = 0; i < n; i++) {
		cout << *(sum + i) << " is score of player  " << i + 1 << endl << "-------------" << endl;
	}
	int* ranks = new int[n];
	for (int i = 0; i < n; i++) {
		ranks[i] = 1;
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (sum[i] < sum[j]) {
				ranks[i]++;
			}
		}
		cout << "The rank of player " << i + 1 << " is: " << *(ranks + i) << endl;
		if(*(ranks + i) == 1) ranked = i+1;
	}
	cout << "The winner is player " << ranked << " !!";
}

void Sortdealer(int**& hand) {
	for (int i = 0; i < 8; i++) {
		for (int j = i + 1; j < 8; j++) {
			if (hand[i][1] > hand[j][1]) {
				swap(hand[i][1], hand[j][1]);
				swap(hand[i][0], hand[j][0]);
			}
		}
	}
}

int checkbai(int** dealer, int n)
{
	Sortdealer(dealer);
	int max = 0;
	int** a = new int*[5];
	for (int i = 0; i < 5; i++) {
		a[i] = new int[2];
	}
	for (int i1 = 0; i1 < n - 5 + 1; i1++)
	for (int i2 = i1 + 1; i2 < n - 5 + 2; i2++)
	for (int i3 = i2 + 1; i3 < n - 5 + 3; i3++)
	for (int i4 = i3 + 1; i4 < n - 5 + 4; i4++)
	for (int i5 = i4 + 1; i5 < n - 5 + 5; i5++)
	{
		a[0][0] = dealer[i1][0]; a[1][0] = dealer[i2][0]; a[2][0] = dealer[i3][0]; a[3][0] = dealer[i4][0]; a[4][0] = dealer[i5][0];
		a[0][1] = dealer[i1][1]; a[1][1] = dealer[i2][1]; a[2][1] = dealer[i3][1]; a[3][1] = dealer[i4][1]; a[4][1] = dealer[i5][1];
		if (max < getStatusOfHand(a)) max = getStatusOfHand(a);
	}
	return max;
}

void S3(int*** hands, int& m, int &turn, int deck[][13], const char* suits[], const char* faces[]) {
	do{
		cout << "\n Input numbers of players: ";
		cin >> m;
	}while (m < 1 || m > 9) ;
	shuffleCards(deck);
	int*** dhands = NULL;
	dhands = dealingForHands(deck, m);
	for (int i = 0; i < m; i++) {
		dhands[i] = dealingForHand(deck, i, m);
	}
	int** dealer = new int*[8];
	for (int i = 0; i < 8; i++) {
		dealer[i] = new int[2];
	}
	for (int i = 0; i < 5; i++) {
		dealer[i][0] = dhands[m - 1][i][0];
		dealer[i][1] = dhands[m - 1][i][1];
	}
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 4; j++) {
			for (int t = 0; t < 13; t++) {
				if (deck[j][t] == 5 * m + i)
				{
					dealer[i + 5][0] = j;
					dealer[i + 5][1] = t;
				}
			}
		}
	}
	int* sumd = new int[m - 1];
	for (int i = 0; i < m - 1; i++) {
		sumd[i] = 0;
	}
	int cardsdealer = 8;
	int scoredeal;
	int turnd;
	cout << "\n Input turns to play: ";
	cin >> turnd;
	//int scoredealer = checkbai(dealer, cardsdealer);
	for (int k = 0; k < turnd; k++) {
		shuffleCards(deck);
		Sleep(1000);
		dhands = dealingForHands(deck, m);
		int scoredealer = checkbai(dealer, cardsdealer);
		for (int t = 0; t<m - 1; t++){
			printHand(dhands[t], suits, faces);
			cout << "Score: " << getStatusOfHand(dhands[t]);
			cout << endl << "--" << endl;
			sumd[t] += getStatusOfHand(dhands[t]);
		}
		for (int i = 0; i < 5; i++) {
			dealer[i][0] = dhands[m - 1][i][0];
			dealer[i][1] = dhands[m - 1][i][1];
		}
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 4; j++) {
				for (int t = 0; t < 13; t++) {
					if (deck[j][t] == 5 * m + i)
					{
						dealer[i + 5][0] = j;
						dealer[i + 5][1] = t;
					}
				}
			}
		}
		for (int i = 0; i < 8; i++)
		{
			cout << "(" << suits[dealer[i][0]] << " , " << faces[dealer[i][1]] << ")" << endl;
		}
		cout << "Score: " << scoredealer << endl;
		cout << "--" << endl;
		scoredeal += scoredealer; // tính tong diemm cua dealer sau turn vòng
	}
	int rankd, scored = 0;
	for (int i = 0; i<m - 1; i++){
		for (int j = i + 1; j<m - 1; j++){
			if (*(sumd + i) > *(sumd + j)){
				rankd = i + 1;
				scored = *(sumd + i);
			}
			else rankd = j + 1; scored = *(sumd + j);
		}
	}
	if (scored >= scoredeal) cout << " Player " << rankd << " win!!" << endl;
	else cout << " Dealer win!!" << endl;
}

void S4andS5easy(int*** hands, int k, int turn, int deck[][13], const char* suits[], const char* faces[]) {
	shuffleCards(deck);
	int*** shands = NULL;
	int cardspler = 8;
	shands = dealingForHands(deck, k);
	for (int i = 0; i < k; i++) {
		shands[i] = dealingForHand(deck, i, k);
	}
	int** pler = new int* [8];
	for (int i = 0; i < 8; i++) {
		pler[i] = new int[2];
	}
	for (int i = 0; i < 5; i++) {
		pler[i][0] = shands[k - 1][i][0];
		pler[i][1] = shands[k - 1][i][1];
	}
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 4; j++) {
			for (int t = 0; t < 13; t++) {
				if (deck[j][t] == 5 * k + i)
				{
					pler[i + 5][0] = j;
					pler[i + 5][1] = t;
				}
			}
		}
	}
	int scorepler = checkbai(pler, cardspler);
	for (int i = 0; i < k-1; i++) {
		printHand(shands[i], suits, faces);
		cout << " Score: " << getStatusOfHand(shands[i]);
		cout << endl << "--" << endl;
	}
	for (int i = 0; i < 8; i++)
	{
		cout << "(" << suits[pler[i][0]] << " , " << faces[pler[i][1]] << ")" << endl;
	}
	cout << "Score: " << scorepler << endl;
	cout << "--" << endl;
	if(getStatusOfHand(shands[0]) > scorepler) cout << " Dealer win!!" << endl;
	else cout << " Player win!!" << endl;
}

void S4andS5medium(int*** hands, int k, int turn, int deck[][13], const char* suits[], const char* faces[]){
	shuffleCards(deck);
	int*** shands = NULL;
	int cardspler = 8;
	shands = dealingForHands(deck, k);
	for (int i = 0; i < k; i++) {
		shands[i] = dealingForHand(deck, i, k);
	}
	cout << "Player's cards: " << endl;
	printHand(shands[0],suits,faces);
	cout << "\n\n Dealer's cards: " << endl;
	printHand(shands[1],suits,faces);
	if(getStatusOfHand(shands[0]) < getStatusOfHand(shands[1])) cout << "Player win!!" << endl;
	else cout << "Dealer win!!" << endl;
}

void S4andS5hard(int*** hands, int k, int turn, int deck[][13], const char* suits[], const char* faces[]){
		shuffleCards(deck);
	int*** shands = NULL;
	int cardspler = 8;
	shands = dealingForHands(deck, k);
	for (int i = 0; i < k; i++) {
		shands[i] = dealingForHand(deck, i, k);
	}
	int** pler = new int* [8];
	for (int i = 0; i < 8; i++) {
		pler[i] = new int[2];
	}
	for (int i = 0; i < 5; i++) {
		pler[i][0] = shands[k - 1][i][0];
		pler[i][1] = shands[k - 1][i][1];
	}
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 4; j++) {
			for (int t = 0; t < 13; t++) {
				if (deck[j][t] == 5 * k + i)
				{
					pler[i + 5][0] = j;
					pler[i + 5][1] = t;
				}
			}
		}
	}
	int scorepler = checkbai(pler, cardspler);
	for (int i = 0; i < k-1; i++) {
		printHand(shands[i], suits, faces);
		cout << "Score: " << getStatusOfHand(shands[i]);
		cout << endl << "--" << endl;
	}
	for (int i = 0; i < 8; i++)
	{
		cout << "(" << suits[pler[i][0]] << " , " << faces[pler[i][1]] << ")" << endl;
	}
	cout << "Score: " << scorepler << endl;
	cout << "--" << endl;
	if(getStatusOfHand(shands[0]) > scorepler) cout << "Player win!!" << endl;
	else cout << "Dealer win!!" << endl;
}
// Ham chinh mau cua van ban
void textcolor(int x)
{
	HANDLE mau;
	mau = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(mau, x);
}

// Hàm d?ch chuy?n con tr? d?n v? trí x,y
void gotoxy(int x, int y)
{
	HANDLE hConsoleOutput;
	COORD Cursor_an_Pos = { x - 1, y - 1 };
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, Cursor_an_Pos);
}

int main()
{
	int** hand = NULL;
	int*** hands = NULL;
	int** r = NULL;
	int n, selection, a[1000];
	int deck[SUITS][FACES];
	int m, turn,k = 2;
	char y;
	system("cls");
	
		for (int i = 0; i < 2; i++)
		{
			gotoxy(1,10);
			textcolor(12);
			cout << "\n                 =============           /`            ____    ___    ___________    _____________  ";
			cout << "\n                ||*      ///||         // ``           |* |   / */    |  *      *|   ||*      ///|| ";
			cout << "\n                || *        ||        //   ``          |  |  /  /     |   _______|   || *        || ";
			cout << "\n                ||        * ||       //     ``         |  | /  /      |   |          || *        || ";
			cout << "\n                ||   *      ||      //       ``        | *|/  /       | * |______    || *        || ";
			cout << "\n                ||///=======|}     //         ``       |      (       |      *   |   ||////////__|| ";
			cout << "\n                ||                 ``         //       |      `       |*  _______|   ||  |  `  `    ";
			cout << "\n                ||                  ``       //        |  | `  `      |   |          ||  |   `  `   ";
			cout << "\n                ||                   ``     //         |* |  `  `     | * |_______   ||  |    `  `  ";
			cout << "\n                ||                    ``   //          |  |   `  `    |           |  ||  |     `  ` ";
			cout << "\n                ||                     ``.//           |__|    `___)  |___________|  ||__|      `___)   ";
		Sleep(800);
		system("cls");
		Sleep(800);
		}
	while (1)
	{
		system("cls");
		textcolor(15);
		cout << "\n\n\n\n\n\n\n                                      ---------- WELCOME TO POKER WORLD ----------- " << endl;
		cout << "\n                                      --------- By Huu Bang and Khanh Duy --------- " << endl;
		textcolor(12);
		cout << "\n                                        * * * * * * * * * * * * * * * * * * * * *";
		cout << "\n                                        *                                       *";
		textcolor(14);
		cout << "\n                                        *           1/ Test Cards               *" << endl;
		textcolor(11);
		cout << "                                        *           2/ Single Player            * " << endl;
		textcolor(10);
		cout << "                                        *           3/ Multiplayer              *" << endl;
		textcolor(15);
		cout << "                                        *           4/ Playing with Dealer      * ";
		textcolor(15);
		textcolor(12);
		cout << "\n                                        *                                       *";
		cout << "\n                                        * * * * * * * * * * * * * * * * * * * * *";
		textcolor(15);
		cout << "\n\n                                              PLEASE CHOOSE A MODE TO PLAY: ";
		cin >> selection;
	

		cout << endl;
		if (selection != 1 && selection != 2 && selection != 3 && selection != 4)
		{
			cout << "\n                                           Invalid Option , Please check it again! " << endl;
			system("pause");
		}
		else if (selection == 1)
		{
			system("cls");
			textcolor(14);
			shuffleCards(deck);
			printCardsShuffling(deck, suits, faces);
			r = createHandTest(deck, a);
			cout << endl;
			system("pause");
		}
		else if (selection == 2)
		{
			system("cls");
			textcolor(11);
			cout << "\n                                   SINGLE PLAYER MODE:" << endl;
			shuffleCards(deck);
			printCardsShuffling(deck, suits, faces);
			hand = dealingForHand(deck);
			cout << " \n\n -------------------------------------------------- 1 Player Mode: -------------------------------------------------- ";
			cout << " \n  5 la bai tren tay nguoi choi la: " << endl;
			printHand(hand, suits, faces);
			CheckHand(hand);
			cout << "\n Do you want to play again? (y/n)";
			cin >> y;
		
		}
		else if (selection == 3)
		{
			system("cls");
			textcolor(10);
			int selection_2;
			cout << "\n\n ---------------------------------------- How many Rounds do you want to Play ? --------------------------------------";
			cout << "\n\n					        1/ Just a Single Round";
			cout << "\n\n					        2/ Play Multiple Rounds";
			cout << "\n\n                                                   Choose an option: ";
			cin >> selection_2;
			switch (selection_2)
			{
			case 1:
			{
					  system("cls");
					  np(hands, deck, n);
					  system("pause");
					  break;
			}
			case 2:
			{
					  system("cls");
					  np2(hands, deck, n);
					  system("pause");
					  break;
			}
			}
		
		}
		else if (selection == 4)
		{
			system("cls");
			int select_dealer,select_dealer2,select_dealer3;
			textcolor(15);
			shuffleCards(deck);
		
			hand = dealingForHand(deck);
			cout << " \n\n -------------------------------------------------- Dealer Mode: -------------------------------------------------- ";
			cout << "\n                                                 1/ N Players vs Dealer";
			cout << "\n                                                 2/ Solo with Dealer";
			cout << "\n                                          Which mode do you want to experience: ";
			cin  >> select_dealer;
			if (select_dealer == 1)
			{
			S3(hands, m, turn, deck, suits, faces);	
			system("pause");
		}
			else if (select_dealer == 2)
			{
				cout << "\n	                                              1/ Easy";
				cout << "\n                                                      2/ Medium";
				cout << "\n                                                      3/ Hard";
				cout << "\n                                          Which mode do you want to experience: ";
				cin  >> select_dealer2;
				if (select_dealer2 == 1)
				{
					S4andS5easy(hands,k,turn,deck,suits,faces);
				}
				else if (select_dealer2 == 2)
				{
					S4andS5medium( hands, k, turn, deck,suits,faces);
				}
				else if (select_dealer2 == 3)
				{
					S4andS5hard(hands, k, turn, deck, suits, faces);
				}
				system("pause");
			}
	}
	delete[] hand;
	_getch();
	}
}
