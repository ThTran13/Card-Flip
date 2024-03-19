#include <iostream>
#include <vector>
#include <cstdlib>
#include <list>
#include <algorithm>
#include <string>

using namespace std;

class card
{
public:
    card(){}; // empty constructor
    card(int number, string suit){
        // constructor with parameters

    };
    // copy constructor
    card(const card &c)
    {
        this->number = c.number;
        this->suit = c.suit;
    };
    // set and get method
    void setValue(int num);
    void setSuit(string csuit);
    int getValue();
    string getSuit();

    // overloading outstream
    friend ostream &operator<<(ostream &out, card &pcard);
    // assignment overloading
    void operator=(const card &c_);

private:
    // private member declarations
    int number;
    string suit;
};
ostream &operator<<(ostream &out, card &pcard) // function of operator << overloading
{
    if (pcard.getValue() == 11)
    {
        out << "["
            << "J, " << pcard.getSuit() << "]" << endl;
    }
    else if (pcard.getValue() == 12)
    {
        out << "["
            << "Q, " << pcard.getSuit() << "]" << endl;
    }
    else if (pcard.getValue() == 13)
    {
        out << "["
            << "K, " << pcard.getSuit() << "]" << endl;
    }
    else if (pcard.getValue() == 14)
    {
        out << "["
            << "A, " << pcard.getSuit() << "]" << endl;
    }
    else
    {
        out << "[" << pcard.getValue() << ", " << pcard.getSuit() << "]" << endl;
    }
    return out;
}

// implementation of assignment overloading
void card::operator=(const card &c_)
{
    number = c_.number;
    suit = c_.suit;
}

// setter method to set card value to a new number
void card::setValue(int num)
{
    this->number = num;
}
// setter to set card's suit to a new suit
void card::setSuit(string csuit)
{
    this->suit = csuit;
}
// get the card value
int card::getValue()
{
    return number;
}
// get the suit value
string card::getSuit()
{
    return suit;
}

class Node // class Node to initialize a node
{
public:
    // initialize variables
    int faceValue;
    string suitValue;
    Node *next;

    // constructor
    Node()
    {
        faceValue = 0;
        suitValue = "";
        next = NULL;
    }

    Node(int faceValue, string suitValue)
    {
        this->faceValue = faceValue;
        this->suitValue = suitValue;
        this->next = NULL;
    }
};

class Deck
{
    // copy constructor:
    Node *head;
    card cardDeck(int, string);
    card cardValue;

public:
    Deck()
    {
        head = NULL;
    };
    // destructor
    ~Deck()
    {
        // while the head-> is not null
        while (head->next != NULL)
        {
            // delete the first node
            deleteNode(1);
        }
        // delete the last node at the pointer's position
        deleteNode(1);
        // printlist to check if all the nodes are deleted
        printList();
    }
    // Functions for inserting node into deck (insertNode), printing deck (printList), deleting singular nodes until end of list (deleteNode),
    // identifies card using inserNode (addCard), shuffling deck (shuffle), dealing cards (deal), replacing cards (replace), and play the
    // game (playFlip).
    void insertNode(int, string);
    void printList();
    void deleteNode(int);
    void addCard(int ci);
    void shuffle();
    void deal();
    void replace(int, string);
    void playFlip();
};
void Deck::deleteNode(int nodeOffset)
{
    Node *temp1 = head, *temp2 = NULL; // initializing pointers
    int ListLen = 0;

    if (head == NULL)
    {
        cout << "List empty." << endl;
        return;
    }

    // Find length of the linked-list.
    while (temp1 != NULL)
    {
        temp1 = temp1->next;
        ListLen++;
    }

    // Check if the position to be
    // deleted is greater than the length
    // of the linked list.
    if (ListLen < nodeOffset)
    {
        cout << "Index out of range"
             << endl;
        return;
    }

    // Declare temp1
    temp1 = head;

    // Deleting the head.
    if (nodeOffset == 1)
    {

        // Update head
        head = head->next;
        delete temp1;
        return;
    }

    // Traverse the list to
    // find the node to be deleted.
    while (nodeOffset-- > 1)
    {

        // Update temp2
        temp2 = temp1;

        // Update temp1
        temp1 = temp1->next;
    }

    // Change the next pointer
    // of the previous node.
    temp2->next = temp1->next;

    // Delete the node
    delete temp1;
}

// Function to insert a new node.
void Deck::insertNode(int faceValue, string suitValue)
{
    // Create the new Node.
    Node *newNode = new Node(faceValue, suitValue);

    // Assign to head
    if (head == NULL)
    {
        head = newNode;
        return;
    }

    // Traverse till end of list
    Node *temp = head;
    while (temp->next != NULL)
    {
        // Update temp
        temp = temp->next;
    }

    // Insert at the last.
    temp->next = newNode;
}
// print out the deck
void Deck::printList()
{
    Node *temp = head;

    // check if the list is empty
    if (head == NULL)
    {
        cout << "List empty" << endl;
        // is list is empty, return
        return;
    }

    // Traverse the list.
    while (temp != NULL) // For temp not NULL, generate cards with facevalues after 11, 12, 13, and 14 respectively
    {
        if (temp->faceValue == 11)
        {
            cout << "J " << temp->suitValue << endl;
        }
        else if (temp->faceValue == 12)
        {
            cout << "Q " << temp->suitValue << endl;
        }
        else if (temp->faceValue == 13)
        {
            cout << "K " << temp->suitValue << endl;
        }
        else if (temp->faceValue == 14)
        {
            cout << "A " << temp->suitValue << endl;
        }
        else
        {
            cout << temp->faceValue << " " << temp->suitValue << endl;
        }
        temp = temp->next;
    }
}

void Deck ::addCard(int ci)
{
    // add an unshuffled deck of cards
    int n;

    n = ci % 13 + 2;
    if (ci < 13) // inserting suit to each card
    {
        insertNode(n, "SPADE");
    }
    else if (ci < 26)
    {
        insertNode(n, "CLUB");
    }
    else if (ci < 39)
    {
        insertNode(n, "DIAMOND");
    }
    else
    {
        insertNode(n, "HEART");
    }
}

void Deck ::shuffle()
{
    int length = 0;
    int card_indices[52];

    //  seeding
    srand(time(NULL));

    // create an array of 52 numbers
    for (int i = 0; i < 52; i++)
    {
        card_indices[i] = i;
    }

    // swap the numbers randomly to shuffled the array of numbers
    for (int i = 0; i < 52; i++)
    {
        int randomIndex1 = rand() % 52;
        int randomIndex2 = rand() % 52;

        int temp = card_indices[randomIndex1];

        card_indices[randomIndex1] = card_indices[randomIndex2];
        card_indices[randomIndex2] = temp;
    }
    // insert the new shuffled deck into linkedlist
    for (int i = 0; i < 52; i++)
    {
        addCard(card_indices[i]);

        // delete the old nodes
        deleteNode(1);
    }

    cout << endl;
}
void Deck::deal()
{
    Node *temp = head;

    cardValue.setSuit(temp->suitValue);
    cardValue.setValue(temp->faceValue);
    deleteNode(1);

    return;
}
void Deck::replace(int cardValue, string suit)
{
    // add a card to the back of the deck
    insertNode(cardValue, suit);
}

void Deck ::playFlip()
{
    double score = 0; // the player's current score
    string reply;

    cout << "play Flip!" << endl;
    for (int i = 0; i < 52; i++)
    {
        // add card in decks
        addCard(i);
    }
    // print out the deck of cards
    printList();

    cout << "shuffled deck: " << endl;
    // shuffle the cards 3 times
    shuffle();
    shuffle();
    shuffle();

    // print the new deck
    printList();

    // the player takes the first card of the deck and placed face down
    for (int i = 0; i < 24; i++)
    {
        deal();
        cout << "type (Y) to turn over or (N) to end the game: " << endl;
        cin >> reply;
        if (reply == "Y")
        {
            // if cardValue = "A"
            if (cardValue.getValue() == 14)
            {
                // recieve 10 points
                score = score + 10;
            }

            // if cardValue = "K" "Q" or J""
            // recieve 10 points
            else if ((cardValue.getValue() == 11) || (cardValue.getValue() == 12) || (cardValue.getValue() == 13))
            {
                score = score + 5;
            }
            // if cardValue = 8, 9, 10 recieved 0 points
            else if ((cardValue.getValue() == 8) || (cardValue.getValue() == 9) || (cardValue.getValue() == 10))
            {
                score = score + 0;
            }
            // if cardValue = 7, lose half their points
            else if (cardValue.getValue() == (7))
            {
                score = score / 2;
            }
            // if cardValue = 2,3,4,5,6, lose all the score
            else if ((cardValue.getValue() == 2) || (cardValue.getValue() == 3) || (cardValue.getValue() == 4) || (cardValue.getValue() == 5) || (cardValue.getValue() == 6))
            {
                score = 0;
            }
        }
        // end the game if the player decided to end
        else if (reply == "N")
        {
            cout << "End game!" << endl;
            cout << "Your score is: " << score << endl;
            return;
        }
        else
        {
            cout << "Wrong reply!" << endl;
            return;
        }
        // if the card is a heart, the player score add 1
        if (cardValue.getSuit() == "HEART")
        {
            score = score + 1;
        }
        // print out the current card value
        cout << cardValue << endl;
        cout << "Your score is: " << score << endl;

        // replace the card at the bottom of the deck
        replace(cardValue.getValue(), cardValue.getSuit());
    }
}

int main()
{
    Deck list;
    list.playFlip(); // initializes playFlip
}