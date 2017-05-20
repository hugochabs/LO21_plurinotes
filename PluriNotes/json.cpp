#include "json.h"
#include "note.h"


json Note::toJson(){
    json j;
    j["id"] = identifier.toStdString();
    j["title"] = title.toStdString();
    //j["dateCreation"] = dateCreation.toString();
    //j["dateLastUpdate"] = dateLastUpdate.toString();
    j["active"] = active;
    return j;
}

/*
void Note::fromJson(json j){
    identifier.fromStdString(j["id"]);
    title.fromStdString(j["title"]);
    dateCreation.fromString(j["dateCreation"]);
    dateLastUpdate.fromString(j["dateLastUpdate"]);
    active = j["active"];
}
*/

json NoteVersions::toJson(){
    json j;
    j["type"] = type;
    for (NoteVersions::iterator it = getIterator() ; !it.isDone() ; it.isNext()){
        j.push_back(it.current().toJson());
    }
    return j;
}

json NoteManager::toJson(){
    json j;
    for(NoteManager::iterator it = getIterator() ; !it.isDone() ; it.isNext()){
        j.push_back(it.current().toJson());
    }
    return j;
}


void NoteManager::save(){
    ofstream file(directory.toStdString()+"plurinotes.json");
    file << toJson();
    file.close();
}

/*
NoteManager NoteManager::load(){
    ifstream file(directory.toStdString()+"plurinotes.json");
    if(!i.good()){
        throw FileNotFoundException(filename);
    }
    NoteManager NM;
    json j;
    file >> j;
    file.close();
    for (json::iterator it = j.begin() ; it != j.end() ; ++it){
        json j2;
        j2 = *it;
        NoteVersions* NV;
        NV->setNoteType(j2["type"]);
        for(json::iterator it2 = j2.begin() ; it2 != j2.end() ; ++it2){
            json note = *it2;
            Note * n;
            n = n->fromJson(note);
            NV->addNote(n);
        }
        NM.addNoteVersion(NV);
    }
    return NM;
}
*/
/*
void NotesManager::load(){
    std::ifstream i(filename.toStdString());
    if(!i.good()){
        throw FileNotFoundException(filename);
    }
    json j;
    i >> j;
    i.close();

    removeAllNotes();

    for(json::iterator it = j.begin() ; it != j.end() ; ++it){
        json note = *it;
        Note * toAdd;
        if(note["type"]=="Article"){
            toAdd = Article::fromJSON(note);
        }

        addNote(toAdd);
    }
}
*/
