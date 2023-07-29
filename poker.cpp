#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <ctime>
#include <map>

enum class Suit 
{

    CLUBS,
    DIAMONDS,
    HEARTS,
    SPADES

};

enum class Rank 
{

    TWO,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    NINE,
    TEN,
    JACK,
    QUEEN,
    KING,
    ACE

};

struct Card 
{

    Rank rank;
    Suit suit;

};

void printCard(const Card& card) 
{

    switch (card.rank) {
    case Rank::TWO:
        std::cout << "2"; break;
        
    case Rank::THREE:
        std::cout << "3"; break;
        
    case Rank::FOUR:
        std::cout << "4"; break;
        
    case Rank::FIVE:
        std::cout << "5"; break;
        
    case Rank::SIX:
        std::cout << "6"; break;
        
    case Rank::SEVEN:
        std::cout << "7"; break;
       
    case Rank::EIGHT:
        std::cout << "8"; break;
       
    case Rank::NINE:
        std::cout << "9"; break;
        
    case Rank::TEN:
        std::cout << "10"; break;
        
    case Rank::JACK:
        std::cout << "J"; break;
      
    case Rank::QUEEN:
        std::cout << "Q"; break;
        
    case Rank::KING:
        std::cout << "K"; break;
       
    case Rank::ACE:
        std::cout << "A"; break;
        
    }

    switch (card.suit) 
    {

    case Suit::CLUBS:
        std::cout << "♣"; break;
        
    case Suit::DIAMONDS:
        std::cout << "♦"; break;
        
    case Suit::HEARTS:
        std::cout << "♥"; break;
       
    case Suit::SPADES:
        std::cout << "♠"; break;
       
    }

}

void initializeDeck(std::vector<Card>& deck) 
{

    deck.clear();

    for (int suit = 0; suit < 4; ++suit) 
    {

        for (int rank = 0; rank < 13; ++rank) 
        {

            Card card;
            card.suit = static_cast<Suit>(suit);
            card.rank = static_cast<Rank>(rank);
            deck.push_back(card);

        }

    }

}

void shuffleDeck(std::vector<Card>& deck) 
{

    std::default_random_engine rng(static_cast<unsigned int>(std::time(nullptr)));
    std::shuffle(deck.begin(), deck.end(), rng);

}

void dealCards(std::vector<Card>& deck, std::vector<Card>& hand, int numCards) 
{

    for (int i = 0; i < numCards; ++i) 
    {

        hand.push_back(deck.back());
        deck.pop_back();

    }

}

void printHand(const std::vector<Card>& hand) 
{

    for (const Card& card : hand) 
    {

        printCard(card);
        std::cout << " ";

    }

    std::cout << std::endl;

}

bool isFlush(const std::vector<Card>& hand) 
{

    Suit suit = hand[0].suit;

    for (size_t i = 1; i < hand.size(); ++i) 
    {

        if (hand[i].suit != suit) 
        {

            return false;

        }

    }

    return true;

}

bool isStraight(const std::vector<Card>& hand) 
{

    std::vector<int> ranks;

    for (const Card& card : hand) 
    {

        ranks.push_back(static_cast<int>(card.rank));

    }

    std::sort(ranks.begin(), ranks.end());

    for (size_t i = 1; i < ranks.size(); ++i) 
    {

        if (ranks[i] != ranks[i - 1] + 1) 
        {

            return false;

        }

    }

    return true;

}

bool hasFourOfAKind(const std::vector<Card>& hand) 
{

    std::map<Rank, int> rankCounts;

    for (const Card& card : hand) 
    {

        rankCounts[card.rank]++;

    }

    for (const auto& pair : rankCounts) 
    {

        if (pair.second == 4) 
        {

            return true;

        }

    }

    return false;

}

bool hasThreeOfAKind(const std::vector<Card>& hand) 
{

    std::map<Rank, int> rankCounts;

    for (const Card& card : hand) 
    {

        rankCounts[card.rank]++;

    }

    for (const auto& pair : rankCounts) 
    {

        if (pair.second == 3) 
        {

            return true;

        }

    }

    return false;

}

bool hasTwoPairs(const std::vector<Card>& hand) 
{

    std::map<Rank, int> rankCounts;

    for (const Card& card : hand) 
    {

        rankCounts[card.rank]++;

    }

    int numPairs = 0;

    for (const auto& pair : rankCounts) 
    {

        if (pair.second == 2) 
        {

            numPairs++;

        }

    }

    return numPairs >= 2;

}

bool hasPair(const std::vector<Card>& hand) 
{

    std::map<Rank, int> rankCounts;

    for (const Card& card : hand) 
    {

        rankCounts[card.rank]++;

    }

    for (const auto& pair : rankCounts) 
    {

        if (pair.second == 2) 
        {

            return true;

        }
    }

    return false;

}

int calculateHandRank(const std::vector<Card>& hand) 
{

    bool isStraightFlush = false;

    if (isFlush(hand) && isStraight(hand)) 
    {

        isStraightFlush = true;

    }

    bool isFourOfAKind = false;

    if (hasFourOfAKind(hand)) 
    {

        isFourOfAKind = true;

    }

    bool isFullHouse = false;

    if (hasThreeOfAKind(hand) && hasPair(hand)) 
    {

        isFullHouse = true;

    }

    bool isFlushHand = false;

    if (isFlush(hand)) 
    {

        isFlushHand = true;

    }

    bool isStraightHand = false;

    if (isStraight(hand)) 
    {

        isStraightHand = true;

    }

    bool isThreeOfAKind = false;

    if (hasThreeOfAKind(hand)) 
    {

        isThreeOfAKind = true;

    }

    bool isTwoPairs = false;

    if (hasTwoPairs(hand)) 
    {

        isTwoPairs = true;

    }

    bool isPair = false;

    if (hasPair(hand)) 
    {

        isPair = true;

    }

    if (isStraightFlush) 
    {

        return 9; // Straight Flush

    }
    else if (isFourOfAKind) 
    {

        return 8; // Four of a Kind

    }
    else if (isFullHouse) 
    {

        return 7; // Full House

    }
    else if (isFlushHand) 
    {

        return 6; // Flush

    }
    else if (isStraightHand) 
    {

        return 5; // Straight

    }
    else if (isThreeOfAKind) 
    {

        return 4; // Three of a Kind

    }
    else if (isTwoPairs) 
    {

        return 3; // Two Pairs

    }
    else if (isPair) 
    {

        return 2; // Pair

    }
    else 
    {

        return 1; // High Card

    }

}

std::string getHandRankName(int rank) 
{

    switch (rank) 
    {

    case 9:
        return "Straight Flush";

    case 8:
        return "Four of a Kind";

    case 7:
        return "Full House";

    case 6:
        return "Flush";

    case 5:
        return "Straight";

    case 4:
        return "Three of a Kind";

    case 3:
        return "Two Pairs";

    case 2:
        return "Pair";

    case 1:
        return "High Card";

    default:
        return "Unknown";
    }

}

int main() 
{

    std::vector<std::vector<Card>> playerHands;
    std::map<int, std::string> playerRankNames;
    std::map<int, int> playerChips;

    const int numPlayers = 4;
    bool continuePlaying = true;

    while (continuePlaying) 
    {

        std::vector<Card> deck;
        initializeDeck(deck);
        shuffleDeck(deck);

        for (int i = 0; i < numPlayers; ++i) 
        {

            std::vector<Card> hand;
            dealCards(deck, hand, 5);
            playerHands.push_back(hand);

            std::cout << "Player " << i + 1 << " hand: ";
            printHand(hand);

            char changeCard;
            int positionOfCard;

            std::cout << "Do you want change your card? (y/n) ";
            std::cin >> changeCard;

            if (changeCard == 'y')
            {

                std::cout << "Give me the position of the card in your hands: ";
                std::cin >> positionOfCard;

                positionOfCard--;

                hand.at(positionOfCard) = deck.back();
                deck.pop_back();

                std::cout << "Player " << i + 1 << " hand: ";
                printHand(hand);

            }

            std::cout << "Do you want change another your card? (y/n) ";
            std::cin >> changeCard;

            if (changeCard == 'y')
            {

                std::cout << "Give me the position of the card in your hands: ";
                std::cin >> positionOfCard;

                positionOfCard--;

                hand.at(positionOfCard) = deck.back();
                deck.pop_back();

                std::cout << "Player " << i + 1 << " hand: ";
                printHand(hand);

            }

            int rank = calculateHandRank(hand);
            std::string rankName = getHandRankName(rank);
            playerRankNames[i + 1] = rankName;
            std::cout << "Player " << i + 1 << " hand rank: " << rankName << std::endl;

            playerChips[i + 1] = 100;

        }

        int winningRank = -1;
        std::vector<int> winningPlayers;

        for (int i = 0; i < numPlayers; ++i) 
        {

            int rank = calculateHandRank(playerHands[i]);

            if (rank > winningRank) 
            {

                winningRank = rank;
                winningPlayers.clear();
                winningPlayers.push_back(i + 1);

            }
            else if (rank == winningRank) 
            {

                winningPlayers.push_back(i + 1);

            }

        }

        std::cout << "Winning hand rank: " << getHandRankName(winningRank) << std::endl;
        std::cout << "Winning player(s): ";

        for (int player : winningPlayers) 
        {

            std::cout << "Player " << player << " ";

        }

        std::cout << std::endl;

        for (int i = 0; i < numPlayers; ++i) 
        {

            if (std::find(winningPlayers.begin(), winningPlayers.end(), i + 1) != winningPlayers.end()) 
            {

                playerChips[i + 1] += 10;

            }
            else 
            {

                playerChips[i + 1] -= 25;

            }

            std::cout << "Player " << i + 1 << " chips: " << playerChips[i + 1] << std::endl;

        }

        // Check if any player has run out of chips

        for (int i = 0; i < numPlayers; ++i) 
        {

            if (playerChips[i + 1] <= 0) 
            {

                std::cout << "Player " << i + 1 << " has run out of chips. Game over!" << std::endl;
                continuePlaying = false;
                break;

            }

        }

        // Check if any player wants to stop playing

        std::string stopPlayingInput;
        std::cout << "Do you want to stop playing? (y/n): ";
        std::cin >> stopPlayingInput;
        if (stopPlayingInput == "y") 
        {

            continuePlaying = false;

        }

        // Clear player hands for the next round

        playerHands.clear();

    }

    return 0;

}