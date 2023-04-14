class Node:
    def __init__(self, key=None):
        self.key = key
        self.next = None
        self.previous = None
class LinkedList: #Clase constructora para una lista simplemente enlazada
    def __init__(self):
        self.head = None
        self.length = 0
    
    def add(self, index, key): #añadir nodo en posicion especifica 
        newNode = Node(key)
        if (index == 0):
            if (self.head):
                newNode.next = self.head
                self.head.previous = newNode
            self.head = newNode 
        else:
            var = self.head
            for i in range(index - 1):
                var = var.next
            if (var == None):
                print("Index out of range")
                return
            if (var.next):
                newNode.next = var.next
                var.next.previous = newNode
            newNode.previous = var
            var.next = newNode
        self.length += 1
            

    def get(self, index): #
        val = self.head
        for i in range(index):
            if (val == None): return None
            val = val.next
        return val

    def remove(self, index):
        var = self.head
        for i in range(index):
            if (var.next == None):
                raise IndexError
                return
            var = var.next
        if (var == None): 
            raise IndexError
            return
        tem = var
        if (index == 0):
            self.head = self.head.next
        if (tem.previous):
            var.previous.next = var.next
        if (tem.next):
            var.next.previous = tem.previous
        self.length -= 1
        return tem
    
    def delete (self, value):
        if(value == self.head.key):
            self.remove(0)
            return True
        else:
            var = self.head
            while(var != None):
                var = var.next
                if(value == var.key):
                    tem = var
                    if (tem.previous):
                        var.previous.next = var.next
                    if (tem.next):
                        var.next.previous = tem.previous
                    self.length -= 1
                    return True
            return False
    def find(self, value):
        var = self.head
        i = 0
        for i in range(self.length):
            if(var.key == value):
                return i
        return None
        
    def pushBack(self, key): #añade un elemento en la ultima posición
        NewNode = Node(key)

        if (self.head is None):
            self.head = NewNode
        else:
            val = self.head
            while (val.next is not None):
                val = val.next

            val.next = NewNode
            NewNode.previous = val
        self.length += 1

  