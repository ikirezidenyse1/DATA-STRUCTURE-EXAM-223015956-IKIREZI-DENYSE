
class TreeNode:
    def __init__(self, data):
        self.data = data
        self.children = []

    def add_child(self, child_node):
        self.children.append(child_node)

    def display(self, level=0):
        print(" " * level * 4 + str(self.data))
        for child in self.children:
            child.display(level + 1)

# Example usage
root = TreeNode("Payments")
card = TreeNode("Card Payments")
upi = TreeNode("UPI Payments")
wallet = TreeNode("Wallet Payments")

root.add_child(card)
root.add_child(upi)
root.add_child(wallet)

card.add_child(TreeNode("Credit Card"))
card.add_child(TreeNode("Debit Card"))
upi.add_child(TreeNode("Google Pay"))
upi.add_child(TreeNode("PhonePe"))

root.display()
