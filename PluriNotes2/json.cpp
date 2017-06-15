#include "json.h"
#include "relation.h"


json& Note::toJson(){
    json& j = *new json;
    j["id"] = identifier.toStdString();
    j["title"] = title.toStdString();
    j["dateCreation"] = QStringFromDate(const_cast<tm*>(getDateCreation())).toStdString();
    j["dateLastUpdate"] = QStringFromDate(const_cast<tm*>(getDateLastUpdate())).toStdString();
    j["noteStatus"] = noteStatus;
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


json& Article::toJson(){
    json& j = *new json;
    json j2;
    j2 = this->Note::toJson();
    for (json::iterator it = j2.begin() ; it != j2.end() ; ++it){
        j[it.key()] = it.value();
    }
    j["text"] = getText().toStdString();
    return j;
}

json& Task::toJson(){
    json& j = *new json;
    json j2;
    j2 = this->Note::toJson();
    for (json::iterator it = j2.begin() ; it != j2.end() ; ++it){
        j[it.key()] = it.value();
    }
    j["action"] = getAction().toStdString();
    j["TaskStatus"] = getStatus();
    return j;
}


json& TaskWithPriority::toJson(){
    json& j = *new json;
    json j2;
    j2 = this->Task::toJson();
    for (json::iterator it = j2.begin() ; it != j2.end() ; ++it){
        j[it.key()] = it.value();
    }
    j["priority"] = getPriority();
    return j;
}

json& TaskWithDeadline::toJson(){
    json& j = *new json;
    json j2;
    j2 = this->Task::toJson();
    for (json::iterator it = j2.begin() ; it != j2.end() ; ++it){
        j[it.key()] = it.value();
    }
    j["deadline"] = QStringFromDate(const_cast<tm*>(getDeadline())).toStdString();
    return j;
}

json& OtherNote::toJson(){
    json& j = *new json;
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


json Couple::toJson(){
    json& j = *new json;
    j["x"] = getX()->toJson();
    j["y"] = getY()->toJson();
    j["label"] = getLabel().toStdString();
    return j;
}


json Relation::toJson(){
    json& j = *new json;
    json j2;
    for(Relation::iterator it = getIterator() ; !it.isDone() ; it.isNext()){
        j2.push_back(it.current().toJson());
    }
    j["couples"] = j2;
    j["title"] = title.toStdString();
    j["description"] = description.toStdString();
    j["RelationOrientation"] = orientation;
    return j;
}

json RelationManager::toJson(){
    json& j = *new json;
    json RM;
    for(RelationManager::iterator it = getIterator() ; !it.isDone() ; it.isNext()){
        RM.push_back(it.current().toJson());
    }
    j["relations"] = RM;
    return j;
}


void RelationManager::save(){
    ofstream file(directory.toStdString()+"relations.json");
    file << toJson();
    file.close();
}

void RelationManager::load(){
    ifstream file(directory.toStdString()+"relations.json");
    if(!file.good()){
        QString message;
        message.fromStdString(directory.toStdString()+"relations.json was not found");
        throw NotesException(message);
    }
    json j;
    file >> j;
    file.close();
    json j2 = j["relations"];
    for (json::iterator it = j2.begin() ; it != j2.end() ; ++it){
        addRelation(&Relation::fromJson(*it));
    }

}


Note& Note::fromJson(json j){
    Note* n = new Note(QString::fromStdString(j["id"]), QString::fromStdString(j["title"]), dateFromQString(QString::fromStdString(j["dateCreation"])), dateFromQString(QString::fromStdString(j["dateLastUpdate"])), j["noteStatus"]);
    return *n;
}

Article& Article::fromJson(json j){
    Article* a = new Article(QString::fromStdString(j["id"]), QString::fromStdString(j["title"]), dateFromQString(QString::fromStdString(j["dateCreation"])), dateFromQString(QString::fromStdString(j["dateLastUpdate"])), j["noteStatus"], QString::fromStdString(j["text"]));
    return *a;
}

Task& Task::fromJson(json j){
    Task* t = new Task(QString::fromStdString(j["id"]), QString::fromStdString(j["title"]), dateFromQString(QString::fromStdString(j["dateCreation"])), dateFromQString(QString::fromStdString(j["dateLastUpdate"])), j["noteStatus"], QString::fromStdString(j["action"]), waiting);
    return *t;
}

TaskWithPriority& TaskWithPriority::fromJson(json j){
    Task& t = Task::fromJson(j);
    TaskWithPriority* twp = new TaskWithPriority(t.getIdentifier(), t.getTitle(), t.getDateCreation(), t.getDateLastUpdate(), t.getNoteStatus(), t.getAction(), waiting, (int)j["priority"]);
    return *twp;
}

TaskWithDeadline& TaskWithDeadline::fromJson(json j){
    Task& t = Task::fromJson(j);
    TaskWithDeadline* twd = new TaskWithDeadline(t.getIdentifier(), t.getTitle(), t.getDateCreation(), t.getDateLastUpdate(), t.getNoteStatus(), t.getAction(), waiting, Note::dateFromQString(QString::fromStdString(j["deadline"])));
    return *twd;
}

OtherNote& OtherNote::fromJson(json j){
    OtherNote* t = new OtherNote(QString::fromStdString(j["id"]), QString::fromStdString(j["title"]), dateFromQString(QString::fromStdString(j["dateCreation"])), dateFromQString(QString::fromStdString(j["dateLastUpdate"])), j["noteStatus"], QString::fromStdString(j["description"]), QString::fromStdString(j["fileName"]), j["type"]);
    return *t;
}


Relation& Relation::fromJson(json j){
    Relation& R = *new Relation;
    R.title = QString::fromStdString(j["title"]);
    R.description = QString::fromStdString(j["description"]);
    R.orientation = oriented;
    json j2 = j["couples"];
    for(json::iterator it = j2.begin() ; it != j2.end() ; it++){
        R.addCouple(&Couple::fromJson(*it));
    }
    return R;
}

Couple& Couple::fromJson(json j){
    Couple& C = *new Couple;
    C.label = QString::fromStdString(j["label"]);
    C.x = &Note::fromJson(j["x"]);
    C.y = &Note::fromJson(j["y"]);
    return C;
}

NoteVersions &NoteVersions::fromJson(json j){
    NoteVersions * NV = new NoteVersions;
    NV->type = j["type"];
    json j2 = j["Versions"];
    for (json::iterator it = j2.begin() ; it != j2.end() ; ++it){
        switch(NV->type){
        case NoteType::A :
        {
            Article& a = Article::fromJson(*it);
            NV->addNote(&a);
        }
        break;
        case NoteType::T :
        {
            Task& t = Task::fromJson(*it);
            NV->addNote(&t);
        }
        break;
        case NoteType::TWD :
        {
            TaskWithDeadline& twd = TaskWithDeadline::fromJson(*it);
            NV->addNote(&twd);
        }
        break;
        case NoteType::TWP :{
            TaskWithPriority& twp = TaskWithPriority::fromJson(*it);
            NV->addNote(&twp);
        }
        break;
        case NoteType::ON:{
            OtherNote& on = OtherNote::fromJson(*it);
            NV->addNote(&on);
        }
        break;
        }
    }
    return *NV;
}


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
}


