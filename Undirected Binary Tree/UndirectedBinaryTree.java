/* Submitted by: 
 * 1. Divya Bhat (mn9386) 
 * 2. Batul Zamin (nd9354) 
 * Problem: Implement the Depth first Search and Breath first Search Algorithms
 * Your algorithms should receive an arbitrary undirected binary tree and a goal node as inputs. 
 * Then it looks for the goal node and returns success/failure if the node is found/not found. 
 * Input file: input.txt
 */

import java.io.File;
import java.io.FileNotFoundException;
import java.util.*;

/* Undirected Binary Tree with root node and searching methods */
class UndirectedBinaryTree {

    int root;
    int numTreeNodes;
    Vector<Integer>[] adjacencyList;

    /* Constructor for UndirectedBinaryTree class*/
    @SuppressWarnings("unchecked")
	public UndirectedBinaryTree(Vector<Vector<Integer>> edges) {
    	root = edges.get(0).get(0);
    	// Since we know that the entered tree is valid, connected and acyclic
    	// number of vertices in the graph/tree = number of edges + 1
    	numTreeNodes = edges.size() + 1; 
    	adjacencyList = new Vector[numTreeNodes + 1];
    	for(int i = 1; i < adjacencyList.length; i++){
    		adjacencyList[i] = new Vector<Integer>();
    	}
    }
    
    /* Method to build tree from given edges */
    public void BuildTree(Vector<Vector<Integer>> edges){
    	/* At index value first node of edge, add its neighbor second node of edge for all the edges */
    	for(Vector<Integer> edge: edges){
    		adjacencyList[edge.get(0)].add(edge.get(1));
    	}
    }
    
    /* Method for DFS in Undirected Binary tree */
    public void DepthFirstSearch(int target) {
    	System.out.println("Starting DFS search in input tree: ");
    	Stack<Integer> stack = new Stack<Integer>();
    	if(root == 0) {
            System.out.println("The node is empty");
            return;
        }
    	// Push root node to stack
		stack.add(root);
		System.out.println("push root " + root + " to stack...");
		// Repeat till stack is not empty...
		while (!stack.isEmpty()) {
			int n = stack.pop();
			System.out.println("pop " + n + " from stack...");
			// Compare node popped to target
			if(n == target){
				System.out.println("DFS: SUCCESS");
				return;
			}
			// Push neighbors of the popped node (from adjacency list) to stack
			for(int i = 0; i < adjacencyList[n].size(); i++){
				stack.add(adjacencyList[n].get(i));
				System.out.println("push " + adjacencyList[n].get(i) + " to stack...");
			}
		}
        System.out.println("DFS: FAILURE");
    }

    /* Method for BFS in Undirected Binary tree, this function also helps to build the tree */
    public void BreadthFirstSearch(int target) {
    	System.out.println("Starting BFS search in input tree: ");
        Queue<Integer> queue = new LinkedList<>();
        if(root == 0) {
            System.out.println("The node is empty");
        }
        // Enqueue root node to queue
        queue.add(root);
        System.out.println("enqueue root " + root + " to queue...");
        // Repeat till queue is not empty...
        while(!queue.isEmpty()) {
            int n = queue.poll();
            System.out.println("dequeue " + n + " from queue...");
            // Compare dequeued node to target
            if(n == target) {
        		System.out.println("BFS: SUCCESS");
        		return;
            }
            // Push neighbors of the dequeued node (from adjacency list) to queue
            for(int i = 0; i < adjacencyList[n].size(); i++){
				queue.add(adjacencyList[n].get(i));
				System.out.println("enqueue " + adjacencyList[n].get(i) + " to queue...");
			}
        }
    	System.out.println("BFS: FAILURE");
    }

    /* Main Method */
	public static void main(String[] args) {
	    /* User selection of searching algorithm */
		System.out.println("Enter 1 for DFS searching or 0 for BFS searching in the tree: ");
		Scanner sc = new Scanner(System.in);
		int algorithm = sc.nextInt();
	    sc.close();
	    
	    // vector of vector to store all the edges from the input file
	    Vector<Vector <Integer>> treeEdges = new Vector<>();
	    
	    int target = -1;
	    
	    try {
	    	/* Read Input to create the undirected binary tree from input.txt file*/
	        File myObj = new File("input.txt");
	        Scanner myReader = new Scanner(myObj);
	        
	        // Read input line by line
	        while (myReader.hasNextLine()) {
	            String data = myReader.nextLine();
	            if (data.equalsIgnoreCase("*")) {
	            	// get the target node
	                if (!myReader.hasNextLine()) {
	                    System.out.println("File is not Valid. As it does not contain the target number");
	                }
	                target = Integer.parseInt(myReader.nextLine());
	            } 
	            else if (data.equalsIgnoreCase("#")) {
	            	// end of input file
	                break;
	            } 
	            else {
	            	// Add each edge to vector of vector treeEdges
	                String[] strArr = data.split(",");
	                int n1 = Integer.parseInt(strArr[0]);
	                int n2 = Integer.parseInt(strArr[1]);
	                Vector<Integer> e = new Vector<Integer>();
	                e.add(n1);
	                e.add(n2);
	                treeEdges.add(e);
	            }
	        }
	        
	        /* Build the tree */
	        UndirectedBinaryTree ubt = new UndirectedBinaryTree(treeEdges);
	        ubt.BuildTree(treeEdges);
            
	        /* Run DFS or BFS algorithm as per user selection*/
		    System.out.println("\nSearching the target " + target);
			if (algorithm == 1) {
				ubt.DepthFirstSearch(target);
			}
			else {
				ubt.BreadthFirstSearch(target);
			}
	        myReader.close();
	    } 
	    catch (FileNotFoundException e) {
	        System.out.println("An error occurred.");
	    }
	  
	}
}
