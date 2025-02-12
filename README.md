A No Limit Texas Hold 'em Poker game played in the CLI.

## Software Requirements

### 1st Priority: The completed product must have
- [X] For scalable play, the user is able to pick the number of players before the game starts (must be > 1).  All players are going to be live people.
- [X] A dealer is randomly chosen & play begins with the next person in line.

For fairness with the deck, the program will:
- [X] accurately create a 52 card deck.
- [X] draw a random card from the deck.
- [X] remove the card from the deck after it's drawn.  
;

- [ ] A player's hole cards are hidden from the other players, by clearing the terminal's previous output & passing the device on to the next player.

The rules of No Limit Texas Hold 'em Poker (without blinds) are enforced:
- [ ] 2 cards are dealt to each player & each player gets to privately look at their cards.
- [X] All players must come to an agreement on an ante before the Pre-Flop round will end.
- [ ] 3 cards are flipped & each player gets to pick an action in the Flop round.
- [ ] 1 Card is flipped & each player gets to pick an action in the Turn round.
- [ ] 1 Card is flipped & each player gets to pick an action in the River round.
- [ ] All players' hole cards are exposed & the winning hand is correctly determined at the Showdown round.
- [ ] If at any point, all other players fold, the last player standing wins the pot.
- [ ] If all players decide to go all-in, skip to the Showdown round.
;

On a player's turn, they are given some of these actions (depends on the state the game is in):
- [X] Folding (removing a player until the game is done).
- [X] Checking (not betting any chips), only available if no other player has bet this round.
- [X] Opening (making the first bet of the game), only available if no other player has bet this round.
- [X] Calling (matching the ante), only available after a bet has been made this round.
- [X] Raising (increase the existing ante by an amount of chips), only available after a bet has been made this round.
;

- [ ] If a player decides to goes all-in, they won't be able to do any more turn actions for the rest of the game.
- [ ] An accurate record of the pot is kept for the duration of one game.
- [ ] An accurate record of each player's chip count is kept for the duration of the program session (meaning it carries over into subsequent games).
- [ ] Before each betting round (the Pre-Flop, Flop, Turn, or River rounds) begins, the ante (minimum that a player can bet this round) is reset to 0.

 At the end of a game:
 - [ ] the pot is added to the winning player's chip count
 - [ ] a new game with the same number of players is started, with all of their last chip counts
 - [ ] however, if a player loses all their chips, they cannot participate in the next game
 - [ ] players lose their hole cards
 - [ ] a new deck is made  
;


### 2nd Priority: Some advancements
 - [ ] Allow the user to choose to use blinds for the game & specify the small and big blind values.
 - [ ] Allow the user to choose the amount of chips each player starts with.
 - [ ] Put in the logic for the proper rules for re-raising.
 - [ ] On the side, always show the last x moves each player made & the current amount of chips they have.
 - [ ] Make the game playable for one person against computer players.


### 3rd priority:  Nice to haves (but not in scope right now)
 - [ ] Neater formatting, always
 - [ ] High score menu of most chips at termination of the program, biggest pot won, best bluff
 - [ ] If a player does you really dirty, give the action option to initiate a gun duel (bc y not)
