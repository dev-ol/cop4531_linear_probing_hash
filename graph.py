
# importing the required module 
import matplotlib.pyplot as plt 
import numpy as np

def main():
    # stores the file names of the results in the results folder
    resultsFiles = ["quadratic_probing", "linear_probing", "double_hashing", "my_hash_probing"]
    
    xs = []
    ys = []

    # going through each result file
    for name in resultsFiles:
        try:
            resultsFile = open('./results/{}.txt'.format(name), 'r')
            
            lines = resultsFile.readlines()
            count = 0
           
            # Strips the newline character
            for line in lines:
                count += 1

                words = line.split()
                #x and y values use to plot graph
                x = float(words[2])
                y = int(words[5])

                xs.append(x);
                ys.append(y);
                
            plotGraph(name, xs,ys)
           
            xs.clear();
            ys.clear();
        except IOError:
            print("\nFile {}.txt doesn't exists\n".format(name))
        except Exception as e:
            print(e)
        finally:    
            resultsFile.close()
    
       
        

def plotGraph(name,xs, ys):
    print("\nCreating Graph for {}.".format(name))

    y2 = generateFunction()
    
    print(y2)
    # plotting the points  
   
    fig, ax_left = plt.subplots()
    fig, ax_left = plt.subplots()
    ax_right = ax_left.twinx()

    
    ax_left.plot(xs,y2, color='black')
    ax_right.plot(xs,ys, color='red')

    
    # giving a title to my graph 
    plt.title('{} graph'.format(name)) 
    
    plt.grid()
    # function to show the plot 

    plt.savefig("graphs/{}.png".format(name))

    print("Graph for {} (png format) is located in the graph folder.".format(name))

    plt.cla()


def generateFunction():
    x = [0.5,0.6,0.7,0.8,0.9, 0.99]
    y = []
    for i in x:
        r = 1/(1-i)
        y.append(r)
    
    return y


main()