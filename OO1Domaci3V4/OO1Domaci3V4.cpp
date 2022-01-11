#include <iostream>
#include <utility>
#include "Player.h"
#include "Team.h"
#include "Pair.h"
#include "PrivilegedTeam.h"
#include "Match.h"

int main() {
	using ndb::Pair, ndb::Player, ndb::Team, ndb::PrivilegedTeam, ndb::Match;
	Player p1("Ibrahimovic", 125);
	Player p2("Messi", 150);
	Player p3("Ronaldo", 175);
	Player p4("Kakka", 125);
	Team* t1 = new Team("Team1", 10);
	t1->join_player(p1,1);
	t1->join_player(p2,3);
	Team* t2 = new PrivilegedTeam("Team2", 10,100);
	t2->join_player(p3,2);
	t2->join_player(p4,4);
	Match m(t1, t2);
	m.play_match();
	std::cout << "Result points: " << m.get_points() << '\n';
	std::cout << m << '\n';
}
