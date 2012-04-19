#include "player.h"
#include "blackjack.h"
#include "utilities.h"

#include <string>
#include <fstream>
#include <exception>
#include <fstream>

std::string Player::_playersFileName = std::string("players.txt");

//Player::Player(std::string name, double balance, BlackJack* game)
//{
//    _name = name;
//    _balance = balance;
//    _bet = 0.0;
//    _hand = Hand();
//    _game = game;
//}

Player::Player(std::ifstream& file, BlackJack* game)
{
    if (!ReadText(file))
        throw InvalidPlayerException();
    _game = game;
}

void Player::WriteBinary(std::ofstream& out)
{
    out << _name << '\0' << _balance; // << _bet; It isn't needed because we don't want to save Player bet;
}

bool Player::ReadText(std::ifstream& file)
{
    file >> _balance;

    getline(file, _name, '\n');

    return !_name.empty();
}

void Player::SetPlayersFileName(std::string playersFileName)
{
    if (!Utilities::FileExists(playersFileName.c_str()))
    {
        std::fstream out (playersFileName.c_str(), std::ios::out | std::ios::binary);
        if (!out.is_open())
            ;//throw exception
        out.close();
    }

    _playersFileName = playersFileName;
}

void Player::PlaceBet(double bet)
{
    if (bet <= 0 || bet > _balance)
        throw InvalidBetException("Invalid bet exception at Player::Set(double bet)!");

    _bet = bet;
    _balance -= bet;

    _game->PlayerBet(this, bet);
}
