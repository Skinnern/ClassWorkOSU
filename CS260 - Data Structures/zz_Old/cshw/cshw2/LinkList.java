class LinkList{
	public Link firstLink;
	LinkList(){
		firstLink = null;
	}
	public boolean isEmpty(){
		return(firstLink == null);
	}
		public void addFirstLink(String Vehicle, boolean Convertable){
		Link newLink = new Link(Vehicle, Convertable);
		newLink.next = firstLink;
		firstLink = newLink;
	}
	public void display(){
		Link nickLink = firstLink;
		while(nickLink!= null){
			nickLink.display();
			if (nickLink.next == null){
				System.out.println("\n\n\nthere are no other items in the list.");
			}
			else{
			System.out.println("Next Link: " + nickLink.next);
		}
			nickLink = nickLink.next;
			System.out.println();
		}
	}
}