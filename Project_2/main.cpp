#include "Navigation.hh"

// 20 20
// .........GDANSK.....
// ........*...........
// ........#...........
// ........#...........
// *##################.
// #SZCZECIN.........#.
// #.................#.
// ##................#.
// .############*#####.
// .#...WARSZAWA.......
// .#..................
// .#############......
// .#...........#......
// .#..WROCLAW.##......
// .#..*.......*.......
// .####.......#KIELCE.
// ......*##.#########.
// .OPOLE..#.*.......#.
// ........#.KRAKOW..#.
// ........###########.
// 0
// 4
// KIELCE KRAKOW 1
// KRAKOW GDANSK 0
// KRAKOW GDANSK 1
// WARSZAWA KRAKOW 1
int main()
{
	Navigation nav;

	nav.get_input();

	// nav.print_map();

	// nav.print_cities();

	//'DEBUG' ending cin
	cin.get();
	return 0;
}