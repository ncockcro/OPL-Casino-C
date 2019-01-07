# OPL-Casino-C

This program is a game called *Casino* and is written in C++.  Casino is a card game which is played by two players and the object is to score the most points by capturing cards.

###The Players

Two players will take turns playing a tournament consisting of one or more rounds. One player is the human and one player is the computer. Each round will consist of the two players capturing cards until there are no more cards left in the deck. Once one of the players reach 21 points, then the tournament will end.

### Setup

A standard 52 deck of cards is used in the game. Initially the first four cards of the deck are dealt to the human and the next four cards are dealt to the computer. Then the next four cards and dealt to the table, placed face up.  Whenever both of the players have exhausted their cards, four more cards will be dealt, the first four to the human, and the next four to the computer. When the deck is empty and both of the players have used all of their cards, the round will end. In Casino, Kings are valued at 13, Queens at 12, and Jacks at 11. Aces can be either 14 or 1. All other cards are face value.

### A Round
The two players take alternate turns until the round is over.

#### A Turn

During the player's turn, they can play exactly one came from their hand, in one of three ways:

- **Build** A build is a group of cards that must be played together.
	**Building a build:** The player can combine the played card with a **loose** card or cards on the table to form a build. (A loose card is a card that is not part of an build) In order to do so:
	1. The player must also have the card in their hand whose value is the sum of the cards in the build, e.g. 2 and 3 loose cards on the table, and the player plays a 5 to create a build of the three cards 2, 3, and 5 because the player also has a 10 card in their hand that they can play in the future to capture the entire build (2 + 3 + 5 = 10). In this scenario, the 2 and 3 cards were loose cards, i.e. they were not part of a build.
	2. The player is required to hold the 10 card in their hand until the build is captured or another players takes over the build.
	3. As the player who most recently added a card to the build, the player becomes its **owner**.

	**Multiple Build:** A player can create multiple builds, all with the same capture card value, e.g., a build of 6 and 3, another of 5 and 4, and yet another of 8 and Ace.

	**Increasing a build:** A player can add a card to a single build owned by an opponent to increase the value of the build if the player also has the card in their hand with the value equal to the increased sum of the build, e.g. the opponent has a build of 6 + 3; the player adds 2 to the build since the player also has a Jack in their hand (6 + 3 + 2 = 11). The player who added the card now becomes the owner of the build. But adding a card to a build cannot be done if the build is part of multiple builds. It cannot be done by a player to their own build.
- **Capture:** The player may play a card to capture one or more cards on the table:
	- Individual card: If the played card matches an individual card on the table, that card must be captured, e.g., if the player plays a 6, the player will capture any and all 6 cards on the table.
	- **Set of cards:** If the played card matches the sum of a set of cards on the table, the player may choose to capture the set of cards or not, e.g., if the player plays an 8, and a 5 and 3 are on the table,  the player may choose to capture both the 5 and 3 from the table with her 8 card. If the player plays an Ace (value of 14), the player can capture a King(value of 13) and another Ace (value of 1) on the table.
	- The above rules apply only as long as the captured cards are not part of a **build**. The player has the option (but is not required) to capture one or more complete builds (single or multiple) whose value is equal to that of the played card.

- **Trail:** The player plays a card that does not match any individual loose card, and therefore, cannot capture any individual loose card. The played card is left on the table, to be captured or incorporated into a build later. Note that if the played card matches a set of cards or a build, since capturing them is not mandatory, the player can choose to trail rather than capture with the card. Trailing option is not available to the owner of a build- since they can capture the build or work towards a multiple build.

#### Round Ending
The round ends when the players have played all of their cards and the deck is empty. Any cards that remain on the table go to the player who captured last. The piles of both of the players are printed out at the end of the round.

#### Score
When a round ends, the points eaarned by each player are calculated based on the cards in each players pile:
- The player with the most cards gets 3 points. If the players have the same number of cards, no one is awarded points.
- The player with the most Spades gets 1 point. If the players have the same number of Spades, no one is awarded points.
- The player with the 10 of Diamonds gets 2 points.
- The player with the 2 of Spades gets 1 point.
- Each player gets one point per Ace.

The scores earned by the two players are determined at the end of a round.
The tournament scores of both the players are updated and printed at the end of the round.

#### Winning the tournament
If either players score reaches or crosses 21 points bythe end of a round, the tournament ends. Otherwise, a new round is started. When the tournament ends, the player with the greater score wins the tournament. If both players go over 21 points in the same round and end up with the same tournament score, the tournament results in a tie.

#### First player
On the first round of the tournament, a coin is flipped and the human player is asked to call the toss to determine the first player. On subsequent rounds, the player who captured last on the previous round plays first.

### Computer players strategy
The computer will play to win. It will display its strategy for every move with the following:
- Which card it plays
- Whether it capture, builds, or trails
- A description as to why it made that particular move

