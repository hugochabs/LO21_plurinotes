#include "json.h"
#include "relation.h"


json Note::toJson(){
    json j;
    j["id"] = identifier.toStdString();
    j["title"] = title.toStdString();
    j["dateCreation"] = QStringFromDate(const_cast<tm*>(getDateCreation())).toStdString();
    j["dateLastUpdate"] = QStringFromDate(const_cast<tm*>(getDateLastUpdate())).toStdString();
    j["active"] = active;
    return j;
}


json NoteVersions::toJson(){
    json j;
    json NV;
    j["type"] = type;
    for (NoteVersions::iterator it = getIterator() ; !it.isDone() ; it.isNext()){
        NV.push_back(it.current().toJson());
    }
    j["Versions"] = NV;
    return j;
}

json NoteManager::toJson(){
    json j;
    json NM;
    for(NoteManager::iterator it = getIterator() ; !it.isDone() ; it.isNext()){
        NM.push_back(it.current().toJson());
    }
    j["NoteVersions"] = NM;
    return j;
}


json Article::toJson(){
    json j;
    json j2;
    j2 = this->Note::toJson();
    for (json::iterator it = j2.begin() ; it != j2.end() ; ++it){
        j[it.key()] = it.value();
    }
    j["text"] = getText().toStdString();
    return j;
}

json Task::toJson(){
    json j;
    json j2;
    j2 = this->Note::toJson();
    for (json::iterator it = j2.begin() ; it != j2.end() ; ++it){
        j[it.key()] = it.value();
    }
    j["action"] = getAction().toStdString();
    j["TaskStatus"] = getStatus();
    return j;
}


json TaskWithPriority::toJson(){
    json j;
    json j2;
    j2 = this->Task::toJson();
    for (json::iterator it = j2.begin() ; it != j2.end() ; ++it){
        j[it.key()] = it.value();
    }
    j["priority"] = getPriority();
    return j;
}

json TaskWithDeadline::toJson(){
    json j;
    json j2;
    j2 = this->Task::toJson();
    for (json::iterator it = j2.begin() ; it != j2.end() ; ++it){
        j[it.key()] = it.value();
    }
    j["deadline"] = QStringFromDate(const_cast<tm*>(getDeadline())).toStdString();
    return j;
}

json OtherNote::toJson(){
    json j;
    json j2;
    j2 = this->Note::toJson();
    for (json::iterator it = j2.begin() ; it != j2.end() ; ++it){
        j[it.key()] = it.value();
    }
    j["description"] = getDescription().toStdString();
    j["fileName"] = getFileName().toStdString();
    j["type"] = getType();
    return j;
}



Note& Note::fromJson(json j){
    Note* n = new Note(QString::fromStdString(j["id"]), QString::fromStdString(j["title"]), dateFromQString(QString::fromStdString(j["dateCreation"])), dateFromQString(QString::fromStdString(j["dateLastUpdate"])), j["active"]);
    return *n;
}

NoteVersions& NoteVersions::fromJson(json j){
    NoteVersions * NV = new NoteVersions;
    NV->type = j["type"];
    json j2 = j["Versions"];
    for (json::iterator it = j2.begin() ; it != j2.end() ; ++it){
        NV->addNote(&Note::fromJson(*it));
    }
    return *NV;
}
/*
void NoteManager::fromJson(json j){
    json j2 = j["NoteVersions"];
    for (json::iterator it = j2.begin() ; it != j2.end() ; ++it){
        NoteVersions NV;
        NV.fromJson(*it);
        addNoteVersion(&NV);
    }
}
*/

void NoteManager::save(){
    ofstream file(directory.toStdString()+"plurinotes.json");
    file << toJson();
    file.close();
}


void NoteManager::load(){
    ifstream file(directory.toStdString()+"plurinotes.json");
    if(!file.good()){
        QString message;
        message.fromStdString(directory.toStdString()+"pluriontes.json was not found");
        throw NotesException(message);
    }
    json j;
    file >> j;
    file.close();
    json j2 = j["NoteVersions"];
    for (json::iterator it = j2.begin() ; it != j2.end() ; ++it){
        addNoteVersion(&NoteVersions::fromJson(*it));
    }
    //return NM;
}

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
