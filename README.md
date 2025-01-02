A No Limit Texas Hold 'em Poker game played in the CLI.

## Software Requirements

### Priority 1: The completed product must have
- [ ] For scalable play, the user is able to pick the number of players before the game starts.  All players are live people.
- [ ] A dealer is randomly chosen & play begins with the next person in line.

For fairness with the deck, the program will:
- [ ] accurately create a 52 card deck.
- [ ] draw a random card from the deck.
- [ ] remove the card from the deck after it's drawn.  
;

- [ ] A player's hole cards are hidden from the other players, by clearing the terminal's previous output & passing the device on to the next player.

The rules of No Limit Texas Hold 'em Poker (without blinds) are enforced:
- [ ] 2 cards are dealt to each player & each player gets to privately look at their cards.
- [ ] All players must come to an agreement on an ante before the Pre-Flop round will end.
- [ ] 3 cards are flipped & each player gets to pick an action in the Flop.
- [ ] 1 Card is flipped & each player gets to pick an action in the Turn.
- [ ] 1 Card is flipped & each player gets to pick an action in the River.
- [ ] All players' hole cards are exposed & the winning hand is correctly determined at the Showdown.
- [ ] If at any point, all other players fold, the last player standing wins the pot.  
;

On a player's turn, they are given one or more of these actions (depends on the round the game is at):
- [ ] Folding, which takes them out until the game is done.
- [ ] Checking (not betting any chips), which is only available if no other player has bet any chips this round.
- [ ] Calling (matching the previous bet).
- [ ] Raising.  
;

- [ ] An accurate record of the pot & each player's chip count is kept for the game.

 At the end of a game:
 - [ ] the pot is added to the winning player's chip count
 - [ ] a new game with the same number of players is started, with all of their last chip counts
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
