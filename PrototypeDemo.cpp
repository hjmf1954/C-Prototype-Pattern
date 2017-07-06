/*
Class <code>Prototype</code> implements an example of the Structural Design Pattern Prototype pattern.
Please note that the comments in this file and the structure are not good C++ practices.
The usage of the C++-sources are to demonstrate the Prototype pattern and not C++ coding.
Used are:
- Type ---- Name --------- Implements ---------
Class       PrototypeDemo  Demo usage of the Prototype Pattern.
Class       CloneFactory   Implements the method for getting the clone.
Class       Item           Dfines virtual methods to enforce implementation in the derived classes.
Class       BasicItem      Implements the generic methods for an Item and uses CloneFactory.
Class       Book           Example implementation using BasicItem and Item.
Class       CD             Example implementation using BasicItem and Item.

* The example uses a simplified (unrealistic) Book and CD as examples.
* The BasicItem abstract class has been introduced to show how a class:
* - Can extend a class
* - Can extend an abstract class
* For the protoype this is not a necessary extension.
*
* All classes are placed in this single file for simplicity and ease of usage.
*
* How useful is the prototype pattern using cloning in C++?
* Since nowadays the new operator in C++ is extremely fast, cloning is not necessary anymore.
* So see the pattern implementation as an example of C++ techniques for clone and
* abstract classes.
*
* See the documentation on https://www.harmfrielink.nl/wiki/index.php/Prototype_(Pattern)
*/

#include <iostream>
#include <sstream>
using namespace std;

/**
 * Abstract Class <code>Item</code> defines the 2 Item-methods.
 */
class Item {
   public:
      virtual Item *makeCopy() {
         return 0;
      }

      virtual string toString() {
         return "";
      }
};

/**
 * Class <code>CloneFactory</code> implements the getter of the cloning factory.
 */
class CloneFactory {
   public:
      Item *getClone(Item *itemSample) {
         return itemSample->makeCopy();
      }
};

/**
 * Class <code>BasicItem</code> implements the elements for all items.
 */
class BasicItem : public CloneFactory {
   protected:
      string title;
      double price;

   public:
      string getTitle() {
         return title;
      }
      void setTitle(string newTitle) {
         title = newTitle;
      }

      double getPrice() {
         return price;
      }
      void setPrice(double newPrice) {
         price = newPrice;
      }
}; // BasicItem

/**
 * Class <code>Book</code> extends the class BasicItem and abstract class Item.
 * Implements prototype for Item Book.
 */
class Book : public BasicItem, public Item {
   private:
      string isbn;

   public:
      Book() {
         cout << "Book has been created." << endl;
      }

      /* Setter. */
      void setISBN(string newISBN) {
         isbn = newISBN;
      }

      /* Getter. */
      string getISBN() {
         return isbn;
      }


      Item *makeCopy() {
         return new Book( *this );
      }

      string toString() {
         std::ostringstream stringStream;
         stringStream << "Book Title: " << title << ", Price: " << price << ", ISBN: " << isbn;
         return stringStream.str();
      }
};

/**
 * Class <code>CD</code> extends the class BasicItem and abstract class Item.
 * Implements prototype for Item CD.
 */
class CD : public BasicItem, public Item {
   private:
      string catNumber;

   public:
      CD() {
         cout << "CD has been created." << endl;
      }

      void setCatNumber(string newCatNumber) {
         catNumber = newCatNumber;
      }

      string getCatNumber() {
         return catNumber;
      }

      Item *makeCopy() {
         return new CD( *this );
      }

      string toString() {
         std::ostringstream stringStream;
         stringStream << "CD Title: " << title << ", Price: " << price << ", CatNumber: " << catNumber;
         return stringStream.str();
      }
};

/**
Class <code>Prototype</code> implements a
It produces an exiterror when the boundaries of the stack are reached.
@author HJM Frielink, Robert Lafore for Saxion
@version 1.0.1.1 - 02 Nov 2015 - Introduction
*/
class PrototypeDemo {
   public:
      /**
       * Creates a book and makes a clone of the book.
       */
      void doBook() {
         // Inits book-1
         Book *book = new Book();
         book->setTitle("The Da Vince Code");
         book->setPrice(10.2f);
         book->setISBN("978-0307474278");
         cout << book->toString();

         cout << endl << endl;

         // Cloning book.
         CloneFactory *cloneFactory = new CloneFactory();
         Book *clonedBook;
         clonedBook = (Book *) cloneFactory->getClone( book );
         clonedBook->setTitle("Inferno");
         clonedBook->setISBN("978-1400079155");
         cout << "Cloned Book: " << clonedBook->toString() << endl;
      }

      /**
       * Creates a CD and makes a clone of the CD.
       */
      void doCD() {
         CD *cd = new CD();
         cd->setTitle("Meddle");
         cd->setPrice(9.90);
         cd->setCatNumber("CDEMD-1061");
         cout << cd->toString() << endl;

         // Cloning of CD.
         CloneFactory *cloneFactory = new CloneFactory();
         CD *clonedCD;
         clonedCD = (CD *) cloneFactory->getClone( cd );
         clonedCD->setPrice(14.90);
         clonedCD->setCatNumber("CDEMD-1987");
         cout << "Cloned CD: " << clonedCD->toString() << endl;
      }
};


/**
 * Main method without any arguments.
 * @param args CLI Arguments (not-used).
 */
int main() {
   PrototypeDemo *ptd = new PrototypeDemo();
   ptd->doBook();
   ptd->doCD();
}  // main
