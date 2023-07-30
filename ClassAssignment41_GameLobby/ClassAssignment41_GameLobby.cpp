#include <iostream>

class Player {
public: 
    Player(const std::string& name = " ");
    std::string GetName() const;
    Player* GetNext() const;
    void SetNext(Player* next);      
private:
    std::string m_Name;
    Player* m_pNext;                //A pointer to another Player object. Allows for a linked list or a node system.
};

Player::Player(const std::string& name) :
    m_Name(name),
    m_pNext(0)                     //Sets pointer to null
{}

std::string Player::GetName() const {
    return m_Name;
}

Player* Player::GetNext() const {
    return m_pNext;
}

void Player::SetNext(Player* next) {
    m_pNext = next;
}

class Lobby {
    friend std::ostream& operator<<(std::ostream& os, const Lobby& aLobby);
public:
    Lobby();
    ~Lobby();
    void AddPlayer();
    void RemovePlayer();
    void Clear();
private:
    Player* m_pHead;        //Pointer that points to a Player object.
};

Lobby::Lobby():
    m_pHead(0)
{}

Lobby::~Lobby() {           //Is called when the Lobby is deleted.
    Clear();
}

void Lobby::AddPlayer() {
    //Create a new player node
    std::cout << "Please enter the name of the new Player: ";
    std::string name;
    std::cin >> name;
    Player* pNewPlayer = new Player(name);

    //if list is empty, make head of list this new player
    if (m_pHead == 0) {
        m_pHead = pNewPlayer;
    }
    //otherwise find the end of the list and add the player there
    else {
        Player* pIter = m_pHead;
        while (pIter->GetNext() != 0) {     //Saying "While the Iter is not 0 (Note for myself lol)...
            pIter = pIter->GetNext();       //get the next Player Object and check for 0
        }
        pIter->SetNext(pNewPlayer);         //Once 0 is found, then set that as the new player.
    }
}

void Lobby::RemovePlayer() {
    if (m_pHead == 0) {
        std::cout << "The game lobby is empty. No Players to remove!";
    }
    else {
        Player* pTemp = m_pHead;
        m_pHead = m_pHead->GetNext();           //Sets the m_mpHead to the next Player's and deletes the original; removing the pointer.
        delete pTemp;
    }
}

void Lobby::Clear() {
    while (m_pHead != 0) {      //Removes all players until 0 is reached
        RemovePlayer();
    }
}

std::ostream& operator<<(std::ostream& os, const Lobby& aLobby) {
    Player* pIter = aLobby.m_pHead;
    os << "\nHere's who's in the game lobby: \n";
    if (pIter == 0) {
        os << "The game lobby is empty.\n";
    }
    else {
        while (pIter != 0) {
            os << pIter->GetName() << "\n";
            pIter = pIter->GetNext();
        }
    }
    return os;
}

int main()
{
    Lobby myLobby;
    int choice;

    do {
        std::cout << myLobby;
        std::cout << "\nGAME LOBBY\n";
        std::cout << "0 - Exit the program. \n";
        std::cout << "1 - Add a player to the lobby. \n";
        std::cout << "2 - Remove a player from the lobby. \n";
        std::cout << "3 - Clear the lobby. \n";
        std::cout << "\n" << "Enter choice: ";
        std::cin >> choice;

        switch (choice) {
        case 0: std::cout << "Adios, amigo"; break;
        case 1:myLobby.AddPlayer(); break;
        case 2:myLobby.RemovePlayer(); break;
        case 3:myLobby.Clear(); break;
        default:std::cout << "Thats not a choice.\n";
        }
    } while (choice != 0);

    system("pause");
}

//Sidenote: I did this whole thing right the first time. #FeelsGood.