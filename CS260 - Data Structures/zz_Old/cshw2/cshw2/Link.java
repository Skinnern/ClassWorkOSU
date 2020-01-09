public class Link {
	public String Vehicle;
	public boolean Convertable;
	public Link next;
	public Link(String Vehicle, boolean Convertable){
	this.Vehicle = Vehicle;
	this.Convertable = Convertable;
	}
	public void display(){
		System.out.println(Vehicle + " is Convertable: " + Convertable);
	}
	public String toString(){
		return Vehicle;
	}
	public static void main(String[] args) {
		LinkList theLinkedList = new LinkList();
		theLinkedList.addFirstLink("Corvette", true);
		theLinkedList.addFirstLink("GMC F150", false);
		theLinkedList.addFirstLink("Bicycle", false);
		theLinkedList.addFirstLink("Jeep", true);
		theLinkedList.display();
		}
}