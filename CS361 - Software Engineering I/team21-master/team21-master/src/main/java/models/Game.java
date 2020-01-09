package models;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Random;

/**
 * Assignment 1: Each of the blank methods below require implementation to get AcesUp to build/run
 */
public class Game {

    public java.util.List<Card> deck = new ArrayList<>();

    public java.util.List<java.util.List<Card>> cols = new ArrayList<>(4);


    public Game(){
        // initialize a new game such that each column can store cards
        //creating columns for the cards to exist, and be interacted with -NSS
        cols.add(new ArrayList<Card>());
        cols.add(new ArrayList<Card>());
        cols.add(new ArrayList<Card>());
        cols.add(new ArrayList<Card>());
    }

    public void buildDeck() {
        for(int i = 2; i < 15; i++){
            deck.add(new Card(i,Suit.Clubs));
            deck.add(new Card(i,Suit.Hearts));
            deck.add(new Card(i,Suit.Diamonds));
            deck.add(new Card(i,Suit.Spades));
        }
    }

    public void shuffle() {
        // shuffles the deck so that it is random
        //int seed
        //Random rnd = new Random();
        //rnd.setSeed(seed)
        long seed = System.nanoTime();
        //made with a seed to have data be repeatable -NSS
        Collections.shuffle(deck, new Random(seed));
    }

    public void dealFour() {
        // remove the top card from the deck and add it to a column; repeat for each of the four columns

        //iterate through four sets and deal four cards - NSS
        for(int i = 0; i < 4; i++){
            cols.get(i).add(deck.get(deck.size()-1));
            //decriment deck size, because after dealing we will have fewer cards -NSS
            deck.remove(deck.size()-1);
            System.out.println("Hello World");

        }
    }

    public void remove(int columnNumber) {
        // remove the top card from the indicated column
        //check if it has a card there -NSS
        if(columnHasCards(columnNumber)) {
            //if it has that card, we want to grab the card and remove it -NSS
            Card c = getTopCard(columnNumber);
            boolean removeCard = false;
            for (int i = 0; i < 4; i++) {
                //here we want to check the number, the suite, and the value of the card being removed compared to the value of the other card that is of the same suite -NSS
                if (i != columnNumber) {
                    if (columnHasCards(i)) {
                        Card compare = getTopCard(i);
                        //check suites
                        if (compare.getSuit() == c.getSuit()) {
                            //compare values
                            if (compare.getValue() > c.getValue()) {
                                removeCard = true;
                            }
                        }
                    }
                }
            }
            if (removeCard) {
                this.cols.get(columnNumber).remove(this.cols.get(columnNumber).size() - 1);
            }
        }


    }

    private boolean columnHasCards(int columnNumber) {
        // check indicated column for number of cards; if no cards return false, otherwise return true
        //so this will be tested for size > 0 to make sure the column is empty - NSS
        if(this.cols.get(columnNumber).size()>0){
            return true;
        }
        return false;
    }

    private Card getTopCard(int columnNumber) {
        return this.cols.get(columnNumber).get(this.cols.get(columnNumber).size()-1);
    }


    public void move(int columnFrom, int columnTo) {
        // remove the top card from the columnFrom column, add it to the columnTo column
        //grab the top card from the column, we will want to interact with, to keep an instance of it
        Card cardToMove = getTopCard(columnFrom);
        //use the provided method to remove the card from
        this.removeCardFromCol(columnFrom);
        //use the add method provided to add the card to its new column -NSS
        this.addCardToCol(columnTo,cardToMove);

    }

    private void addCardToCol(int columnTo, Card cardToMove) {
        cols.get(columnTo).add(cardToMove);
    }

    private void removeCardFromCol(int colFrom) {
        this.cols.get(colFrom).remove(this.cols.get(colFrom).size()-1);
    }
}
