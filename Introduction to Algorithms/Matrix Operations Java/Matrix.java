//Program 3: Matrix
//Justin Wong, jujwong
//CS101 Tantalo F14

class Matrix {
    private class Entry{
	int column;
	double value;
	Entry(int col, double val){
	    column = col;
	    value = val;
	}

	public boolean equals(Object object){
	    if(object == null || !(object instanceof Entry)){
		System.out.println("Entry:Equals: incorrect parameter type");
		return false;
	    }
	    return ((Entry)object).value == value && ((Entry)object).column == column;
	}


    // overrides Object's toString() method
	public String toString(){
	    return "(" + column + ", " +  value + ")";
	}
    }

    private List[] matrix;
    private int NNZ;

    // Makes a new n X n zero Matrix. pre : n >=1
    public Matrix(int n){
	if (n < 1){
	    System.out.println("Please enter a valid matrix size");
	    return;
	}
	matrix = new List[n];
	for (int i = 0; i < n; i++) matrix[i] = new List();
	NNZ = 0;
    }

    // Returns n, the number of rows and columns of this matrix
    public int getSize(){
	return matrix.length;
    }

    // Returns the number of non-zero entries in this Matrix
    public int getNNZ(){
	return NNZ; 
    }
    
    // overrides Object's equals() method
    public boolean equals(Object x){
	// checks for correct parameters
	if (x == null || !(x instanceof Matrix)) {
	    System.out.println("Matrix:equals: incorrect parameter");
	    return false;
	}
	Matrix temp = (Matrix)x;
	// checks for equal lengths
	if(temp.getSize() != matrix.length){
	    return false;
	}
	// compares list entries
	for(int i = 0; i < matrix.length; i++){
	    if(!(matrix[i].equals(temp.matrix[i]))){
		return false;
	    }
	}
	return true;
    }
    
    // sets this Matrix to the zero state
    public void makeZero(){
	// clears all the lists
	for(int i = 0; i < matrix.length; i++){
	    matrix[i].clear();
	}
	NNZ = 0;
    }
    
    // returns a new Matrix having the same entries as this Matrix
	// if scalar is 0 then everything is 0
    //iterates over the rows
	// checks to make sure objects in list are of type Entry
	// copies over the column and value
	// number of non-zero entries will be the same
    public Matrix copy(){
	Matrix copy = new Matrix(matrix.length);
	for(int row = 0; row < matrix.length; row++){
	    List old = matrix[row];
	    List fresh = copy.matrix[row];
	    for(old.moveTo(0); old.getIndex() >= 0; old.moveNext()){
		Object object = old.getElement();
		if (object == null || !(object instanceof Entry)) {
		    System.out.println("Matrix:copy: Not correct type");
		    return null;
		}
		Entry ij = (Entry)object;
		Entry ijcopy = new Entry(ij.column, ij.value);
		fresh.append(ijcopy);
	    }
	}
	copy.NNZ = NNZ;
	return copy;
    }

    // changes ith row, jth column of this Matrix to x
	// iterates over columns of "row" (list) 
	//checks to make sure objects in list are of type Entry
    public void changeEntry(int i, int j, double x){
	if( (i + j) < 2 || (i + j) > (2 * matrix.length)){
	    System.out.println("Matrix:changeEntry: Indices out of bounds");
	    return;
	} 
	List row = matrix[i - 1];
	if(row == null) System.out.println("Matrix:ChangeEntry: row is Null");
	Entry ij = null;
	for(row.moveTo(0); row.getIndex() >= 0; row.moveNext()){
	    Object object = row.getElement();
	    if (object == null || !(object instanceof Entry)) {
		System.out.println("Matrix:changeEntry: Not correct types");
		return;
	    }
	    ij = (Entry)object;
	    if(ij.column < j) continue;
	    break;
	}
	// if the index doesn't exist and x isn't 0
	if(row.getIndex() == -1 && x != 0){
	    row.append(new Entry(j, x));
	    NNZ++;
	}else if (ij != null && ij.column == j){
	    // if new value is 0 and the node exists remove it
	    // and decrement NNZ otherwise insert
	    if(x == 0){
		row.delete();
		NNZ--;
	    } else {
		ij.value = x;
	    }
	} else {
	    if(x != 0){
		row.insertBefore(new Entry(j, x));
		NNZ++;
	    }
	}
	
    }

    // returns the scalar product of this Matrix and x
	// if scalar is 0 then everything is 0
	// checks to make sure objects in list are of type Entry
	// copies over the column and value * scalar
    public Matrix scalarMult(double x){
	if(x == 0) this.makeZero();
	Matrix copy = new Matrix(matrix.length);
	for(int row = 0; row < matrix.length; row++){
	    List old = matrix[row];
	    List fresh = copy.matrix[row];
	    for(old.moveTo(0); old.getIndex() >= 0; old.moveNext()){
		Object object = old.getElement();
		if (object == null || !(object instanceof Entry)) {
		    System.out.println("Matrix:copy: Not correct type");
		    return null;
		}
		Entry ij = (Entry)object;
		Entry ijcopy = new Entry(ij.column, (ij.value) * x);
		fresh.append(ijcopy);
	    }
	}
	copy.NNZ = NNZ;
	return copy;
    }

    // returns a new Matrix that is the sum of this Matrix with M
	// First it checks in the Matrix passed is the same matrix,
	// if yes then it will return scalarMult(2).
	// if not then it will add up columns, least to greatest using a variation
	// of the merge sort algorithm.
    // In iterating over each row (n times) and accessing each element in both lists
    // (a + b) times, the order of this function is theta(n + a + b).
    public Matrix add(Matrix M){
	if(matrix.length != M.matrix.length){
	    System.out.println("Matrix:add: different matrix sizes");
	    return null;
	}
	// if it is the exact same matrix then just mutiply it by 2.
	// Improves efficiency for such cases
	// to theta(n+a) instead of theta(n+a+b);
	if(M == this) return this.scalarMult(2);
	Matrix copy = new Matrix(matrix.length);
	for(int row = 0; row < matrix.length; row++){
	    List one = matrix[row];
	    List two = M.matrix[row];
	    List sum = copy.matrix[row];
	    // this algorithm does addition much like 
	    // the "merging" process in merge sort
	    one.moveTo(0);
	    two.moveTo(0);
	    // iterates through each list
	    while(one.getIndex() >= 0 && two.getIndex() >= 0){
		Entry r = (Entry)(one.getElement());
		Entry l = (Entry)(two.getElement());
		copy.NNZ++;
		if(r.column == l.column){
		    if(r.value + l.value != 0){
			sum.append(new Entry(r.column, r.value + l.value));
		    } else {
			NNZ--;
		    }
		    one.moveNext();
		    two.moveNext();
		} else if (r.column < l.column){
		    sum.append(new Entry(r.column, r.value));
		    one.moveNext();
		} else {
		    sum.append(new Entry(l.column, l.value));
		    two.moveNext();
		}
	    }
	    // if both cursors are OFF then exit the loop
	    if (one.getIndex() == two.getIndex()) continue;
	    // if either cursor is still ON then append the rest
	    List rest = (one.getIndex() >= 0)? one : two;
	    while(rest.getIndex() >= 0){
		Entry fin = (Entry)(rest.getElement());
		copy.NNZ++;
		sum.append(new Entry(fin.column, fin.value));
		rest.moveNext();
	    }
	    
	}
	return copy;
    }

    
    // returns a new Matrix that is the difference of this Matrix with M
    // First checks if the matrix passed is the same one.
    // If yes, return the scalarMult(2) reducing cost to theta(n + a)
    // Else subtract the columns from least to greatest, using
    // a variation of the merging algorithm from merge sort. By iterating
    // over each row (n times) and accessing each element in both lists
    // (a + b) times, the order of this function is theta(n + a + b).
    public Matrix sub(Matrix M){
	if(matrix.length != M.matrix.length){
	    System.out.println("Matrix:sub: different matrix sizes");
	    return null;
	}
	// if it is the exact same matrix then return the 0 matrix
	if(M == this) return new Matrix(matrix.length);

	Matrix copy = new Matrix(matrix.length);
	//for loop that iterates over rows
	for(int row = 0; row < matrix.length; row++){
	    List one = matrix[row];
	    List two = M.matrix[row];
	    List sum = copy.matrix[row];
	    
	    // this algorithm does subtraction much like 
	    // the "merging" process in merge sort
	    // the values in two will be subtracted
	    // the values in one will be added
	    one.moveTo(0);
	    two.moveTo(0);
	    while(one.getIndex() >= 0 && two.getIndex() >= 0){
		Entry r = (Entry)(one.getElement());
		Entry l = (Entry)(two.getElement());
		copy.NNZ++;
		if(r.column == l.column){
		    if(r.value - l.value != 0){
			sum.append(new Entry(r.column, r.value - l.value));
		    } else {
			NNZ--;
		    }
		    one.moveNext();
		    two.moveNext();
		} else if (r.column < l.column){
		    sum.append(new Entry(r.column, r.value));
		    one.moveNext();
		} else {
		    sum.append(new Entry(l.column, 0 - l.value));
		    two.moveNext();
		}
	    }

	    // if both cursors are OFF then exit the loop
	    if (one.getIndex() == two.getIndex()) continue;
	    // if either cursor is still ON then append the rest
	    List rest = (one.getIndex() >= 0)? one : two;
	    int sign = (one.getIndex() >= 0)? 1 : -1;
	    while(rest.getIndex() >= 0){
		Entry fin = (Entry)(rest.getElement());
		copy.NNZ++;
		sum.append(new Entry(fin.column, sign * fin.value));
		rest.moveNext();
	    }
	}
	return copy;
    }
    
    // returns the transpose of the matrix
	//iterates over current matrix rows and
	//converts column indexes into row indexes
    public Matrix transpose(){
	Matrix copy = new Matrix(matrix.length);
	for(int i = 0; i < matrix.length; i++){
	    List row = matrix[i];
	    for(row.moveTo(0); row.getIndex() >= 0; row.moveNext()){
		Entry entry = (Entry)(row.getElement());
		int line = entry.column - 1;
		copy.matrix[line].append(new Entry(i + 1, entry.value));
	    }
	}
	copy.NNZ = NNZ;
	return copy;
    }
    
    // returns a new Matrix that is the product of this matrix with M
	// checks both matrices if either is the 0 matrix return a 0 matrix
	// using transpose to carry row to row vector multiplication
    public Matrix mult(Matrix prod){
	if(matrix.length != prod.matrix.length){
	    System.out.println("Matrix:mult: invalid size parameter");
	    return null;
	}
	
	Matrix copy = new Matrix(matrix.length);
	if(NNZ == 0 || prod.NNZ == 0) return copy;
	Matrix trans = prod.transpose();
	for(int i = 0; i < matrix.length; i++){
	    // if the list length is 0 skip
	    if(matrix[i].length() == 0) continue;
	    for(int j = 0; j < matrix.length; j++){
		if(trans.matrix[j].length() == 0) continue;
		double result = dot(matrix[i] , trans.matrix[j]);
		if(result != 0){
		    copy.matrix[i].append(new Entry(j + 1, result));
		    copy.NNZ++;
		}
	    }
	}
	return copy;
    }

    // vector dot product on two lists
    private static double dot(List P, List Q){
	double result = 0;
	P.moveTo(0);
	Q.moveTo(0);
	while(P.getIndex() >= 0 && Q.getIndex() >= 0){
	    Entry p = (Entry)(P.getElement());
	    Entry q = (Entry)(Q.getElement());
	    if(p.column == q.column){
		result += p.value * q.value;
		P.moveNext();
		Q.moveNext();
	    } else if (p.column < q.column){
		P.moveNext();
	    } else {
		Q.moveNext();
	    }
	}
	return result;
    }
    
    // toString method for Matrix
    public String toString(){
	String ret = "";
	for(int i = 0; i < matrix.length; i++){
	    if(matrix[i].length() > 0){
		ret += (i+1) + ": " +  matrix[i] + "\n";
	    }
	    
	}
	return ret;
    }

}