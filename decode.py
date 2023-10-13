import Person as schema_generated_person
import Client as schema_generated_client
import ClientType as schema_generated_clientType
import Group as schema_generated_group
import ClientList as schema_generated_clientList
import flatbuffers

# Open the binary file for reading
with open('fb_combined.bin', 'rb') as file:
    data = file.read()

# Access data from the deserialized buffer
buf = flatbuffers.Builder(0)
buf.Bytes = data  # Set the buffer's data directly

# Read the root object (ClientList)
client_list = schema_generated_clientList.ClientList.GetRootAsClientList(buf.Bytes, 0)

# Print the number of clients
print(f"Number of Clients: {client_list.ClientsLength()}")

# Loop through the clients
for i in range(client_list.ClientsLength()):
    client = client_list.Clients(i)

    client_type = client.Type()
    client_data = None

    if client_type == schema_generated_clientType.ClientType.Person:
        client_data = client.Person()
        name = client_data.Name().decode('utf-8')
        age = client_data.Age()
        weight = client_data.Weight()
        gender = client_data.Gender().decode('utf-8')
        print("Client Type: Person")
        print(f"Name: {name}")
        print(f"Age: {age}")
        print(f"Weight: {weight}")
        print(f"Gender: {gender}")

    if client_type == schema_generated_clientType.ClientType.Group:
        client_data = client.Group()
        group_name = client_data.GroupName().decode('utf-8')
        average_age = client_data.AverageAge()
        average_weight = client_data.AverageWeight()

        # Correctly access the Names vector
        names = [client_data.Names(i).decode('utf-8') for i in range(client_data.NamesLength())]

        print("Client Type: Group")
        print(f"Group Name: {group_name}")
        print(f"Average Age: {average_age}")
        print(f"Average Weight: {average_weight}")
        print("Names:", ', '.join(names))

