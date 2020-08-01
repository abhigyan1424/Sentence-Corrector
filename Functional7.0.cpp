#include<bits/stdc++.h>
using namespace std;

#define ll long long

int NumberOfWords = 10005;  // No.of words to be read from the Dictionary
int Count = 1;

string str[10005];       // Array of strings to store words from the Dictionary
vector <string> vect;

void ReadDictionary()       // Reading the Dictionary File.
{
    //string str[3000]
    int i = 0;
    ifstream file;
    file.open("Dictionary.txt");
    while(!file.eof())
    {
        getline(file,str[i]);
        //cout<<str[i]<<"\n";
        i+=1;
    }
    file.close();
}

void ReadOutput()           // Reading the Decoded Output File line by line.
{
    vect.clear();
     // filestream variable file
    fstream file;
    //vector <string> vect;
    string word, t, q, filename;
    // filename of the file
    filename = "PseudoInput.txt";


    // opening file
    file.open(filename.c_str());

    // extracting words from the file
    while (file >> word)
    {
        // displaying content
        //cout << word << endl;  //\n over endl as endl will flush the stream again which is useless in cpp as already done by cout/cin
        vect.push_back(word);
        cout<<word<<" ";
    }
    /*for(int i =0; i<vect.size();i++)
    {
        cout<<vect[i]<<" \n";
    }*/
}

int min(int x, int y, int z)                // min doesn't take 3 arguments
{
    return min(min(x, y), z);
}

int editDistDP(string str1, string str2, int m, int n)
{
    //DP Table/Matrix for storing subproblem values
    int dp[m+1][n+1];
    int x;

    //Here using Bottom-Up Approach, Memoization version can be implemented also perhaps
    for (int i=0; i<=m; i++)
    {
        for (int j=0; j<=n; j++)
        {
            // If first string is empty, only option is to
            // insert all characters of second string
            if (i==0)
                dp[i][j] = j;  // Min. operations = j

            // If second string is empty, only option is to
            // remove all characters of second string
            else if (j==0)
                dp[i][j] = i; // Min. operations = i

            // If last characters are same, ignore last char
            // and recur for remaining string
            else if (str1[i-1] == str2[j-1])
                dp[i][j] = dp[i-1][j-1];

            // If the last character is different, then taking all
            // possibilities and find the minimum
            else
                dp[i][j] = 1 + min(dp[i][j-1],  // Insertion
                                   dp[i-1][j],  // Deletion
                                   dp[i-1][j-1]); // Substitution
        }
    }

    x = dp[m][n];
    return x;               // Added for avoiding the return issue of storing value of a 2D array to a vector
}

/*vector <string> hashTable[20];
int hashTableSize=20;

/*int hashFunc(string st)
{
    return(st.length()%10);
}
*/
vector<vector<string> > v; // vector passed to Cartesian Function
//vector<string> temp;
/*void InsertTemp(string s)
{
    temp.push_back(s);
}

void InsertMain(vector<string> t)
{
    //v.push_back(vector<string>());
    // Compute the index using Hash Function
    // int index = hashFunc(s);
    // Insert the element in the linked list at the particular index
    v.push_back(t);
} */
ofstream file3;           //

void cartesian( vector<vector<string> >& va, int coun ) {
  int index = 0;
  vector<string> HashTable[coun];
  //ofstream file3;
  //file3.open("FinalOutput.txt");

  auto product = []( long long a, vector<string>& b ) { return a*b.size(); };
  const long long N = accumulate( v.begin(), v.end(), 1LL, product );
  vector<string> u(v.size());
  for( long long n=0 ; n<N ; ++n )
    {
        lldiv_t q { n, 0 };
        for( long long i=v.size()-1 ; 0<=i ; --i ) {
          q = div( q.quot, v[i].size() );
          u[i] = v[i][q.rem];
        }
        for( string x : u )
        {
            cout << x << ' ';
            HashTable[index].push_back(x);
        }// TBH N is Count itself
        index++;
        cout << '\n';
  }
    vector<string>::iterator ite;
    for (int i = 0; i < coun; i++)
    {
        for (ite = HashTable[i].begin();ite < HashTable[i].end(); ite++ )
        {
            if(file3.is_open())
            {
                file3<<*ite<<" ";
            }
        }
        file3<<"\n";
    }
}

int main(int argc, char** argv)
{
    string FileName;
    FileName = argv[1];
    int w =0;
    fstream file;
    fstream file2;
    string line;
    file3.open("Final2.txt");
    file.open(FileName + ".txt");
    cout<<"Loading the Dictionary :\n\n";
    ReadDictionary();
    while((w<5)&&(!file.eof()))
        {
            vector<string> ar;
            getline(file,line);
            //cout<<line<<"\n";
            ar.push_back(line);
            file2.open("PseudoInput.txt");
            vector<string>::iterator ite;
            ite = ar.begin();
            file2<<*ite;
            file2<<"\n";
            file2.close();

            //ll unigram = 100000;
            string input;
            int i,x,least,num;
            least = 20 ;                //arbitrary large value of edit distance
            vector<int> edist;          // Temporarily choosing vector, less memory efficiency..


            //cout<<"str[5000] :"<<str[4999]<<"Hi\n";

            //cout<<"\nEnter the word to be corrected :\n";
            //cin>>input;
            cout<<"Reading the ASR Output File :\n";
            ReadOutput();
            int vectsize = vect.size();
            cout<<"\n\nCorrected sequence with reference to 10K words and unigram Probabilities :\n";

            for(int j=0;j<vect.size();j++)
            {
                least = 30;             // for resolving the least = 0 bug

               // cout<<" \nThe current ASR Output Word is : "<<vect[j]<<"\n";
               // cout<<"The corresponding Edit distances are\n";

                edist.clear();              // TO clear the vector for the next word
                for(i=0;i<NumberOfWords;i++)                //Calculating the Edit Distance wrt a given word
                {
                    x = editDistDP(vect[j],str[i],vect[j].length(),str[i].length());
                    //cout<<x;
                    edist.push_back(x);                     // edist.push_back(x) doesn't work as edist size will keep on increasing a lot(by 3000 for every word)

                    //cout<<"\n";
                    least = min(least,x);      // When reading multiple words if least = 0 for some word, then this statement fails.. so again least = 20
                }
                //cout<<"Least edit distance :"<<least<<"\n";

                if(least!=0)
                {
                    int m =0;
                    num = count(edist.begin(), edist.end(), least);
                    //cout<<"No of words with same edit Distance are:"<<num<<"\n";
                    if(num == 1)
                    {
                        //Can directly replace the Incorrect words...
                        vector<int>::iterator it = find(edist.begin(), edist.end(), least);
                        int index = distance(edist.begin(), it);
                        //vect[j] = str[index];
                        //for(int k=0;k<1;k++)
                        //{
                            //insrt(str[index],j);                             // Inserting into the hashTable for output
                            cout<<str[index]<<" ";                           // Earlier this was printing all the least distant words, now only the best word sequence based on unigram
                            vector<string> temp;
                            temp.push_back(str[index]);
                            v.push_back(temp);
                        //}

                    }
                    else                                                     // For Multiple least edit distances
                    {
                        int k;
                        vector<string> temp;
                        vector<int>::iterator iter = edist.begin();
                        while ((iter = find(iter, edist.end(), least)) != edist.end())
                        {
                            // Do something with iter
                            iter = find(iter, edist.end(), least);
                            int index = distance(edist.begin(),iter);
                            //unigram = min(unigram,index)                            // For storing the first index to print later basically
                            //vect[j] = str[index];
                            // Will print only once(first) but store everything in the hash table
                            if(m==0)
                            {
                                cout<<str[index]<<" ";
                                m++;
                            }                                 // modifying the output itself but not showing the various text combinations
                            //insrt(str[index],j);
                            temp.push_back(str[index]);
                            //break;                            // Temporarily doing this for the uni-gram version only.
                            iter++;
                        }
                        v.push_back(temp);
                        Count = Count*num;          // To track the size of HashTable
                        //cout<<"The most probable word output is :"<<input<<"\n";
                    }
                }
                else if (least == 0)
                {
                    cout<<vect[j]<<" ";
                    //insrt(vect[j],j);
                    vector<string> temp;
                    temp.push_back(vect[j]);
                    v.push_back(temp);
                }
            }
            cout<<"\n\nBest Possible Outcomes:\n";
            cartesian(v,Count);
            cout<<"\n";
            v.clear();
            w =w+1;
            /*ofstream file;
            file.open("FinalOutput.txt");

            //Printing the contents of the hash table
            cout<<"\n\nPrinting the contents of the hash table:\n";
            vector<string>::iterator ite;
            for (int i = 0; i < vectsize; i++)
            {
                for (ite = hashTable[i].begin();ite < hashTable[i].end(); ite++ )
                {
                    if(file.is_open())
                    {
                        file<<*ite<<" ";
                    }
                }
                cout<<"\n";
            }
            file.close();
            */
            // Writing the possible outputs to a file, upon which Language Model will be applied.


       }
    file.close();
    file3.close();
    return 0;
}

