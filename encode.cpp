#include "schema_generated.h"
#include <flatbuffers/flatbuffers.h>
#include <fstream>
#include <iostream>

int main(int argc, char *argv[]) {
    // Create a FlatBuffer builder
    flatbuffers::FlatBufferBuilder builder;

    // Create and populate Person object for the first client
    auto personName1 = builder.CreateString("Ram");
    auto personGender1 = builder.CreateString("Male");
    schema::PersonBuilder personBuilder1(builder);
    personBuilder1.add_name(personName1);
    personBuilder1.add_age(21);
    personBuilder1.add_weight(76.0f); // Use 76.0f instead of 76
    personBuilder1.add_gender(personGender1);
    auto person1 = personBuilder1.Finish();

    // Create and populate Group object for the second client ("FightClub")
    auto groupName2 = builder.CreateString("FightClub");

    std::vector<flatbuffers::Offset<flatbuffers::String>> groupNames2;
    groupNames2.push_back(builder.CreateString("Ram"));
    groupNames2.push_back(builder.CreateString("Shayam"));
    groupNames2.push_back(builder.CreateString("Raghuveer"));
    auto groupNamesVector2 = builder.CreateVector(groupNames2);

    schema::GroupBuilder groupBuilder2(builder);
    groupBuilder2.add_groupName(groupName2);
    groupBuilder2.add_averageAge(24);
    groupBuilder2.add_averageWeight(66.0f); // Use 66.0f instead of 66
    groupBuilder2.add_names(groupNamesVector2);
    auto group2 = groupBuilder2.Finish();

    // Create a Client object for the first client as a Person client
    schema::ClientBuilder clientBuilder1(builder);
    clientBuilder1.add_type(schema::ClientType_Person);
    clientBuilder1.add_person(person1);
    auto client1 = clientBuilder1.Finish();

    // Create a Client object for the second client as a Group client
    schema::ClientBuilder clientBuilder2(builder);
    clientBuilder2.add_type(schema::ClientType_Group);
    clientBuilder2.add_group(group2);
    auto client2 = clientBuilder2.Finish();

    // Create a ClientList with a vector of Client objects
    std::vector<flatbuffers::Offset<schema::Client>> clients;
    clients.push_back(client1);
    clients.push_back(client2);
    auto clientsVector = builder.CreateVector(clients);

    schema::ClientListBuilder clientListBuilder(builder);
    clientListBuilder.add_clients(clientsVector);
    auto clientList = clientListBuilder.Finish();

    // Finish building the buffer
    builder.Finish(clientList);

    // Serialize to a binary buffer
    const uint8_t *serializedData = builder.GetBufferPointer();
    int serializedSize = builder.GetSize();

    // Write to a binary file
    std::ofstream outputFile("fb_combined.bin", std::ios::binary);
    outputFile.write(reinterpret_cast<const char *>(serializedData), serializedSize);

    // Print the number of clients at the end
    std::cout << "Number of Clients: " << clients.size() << std::endl;

    return 0;
}

