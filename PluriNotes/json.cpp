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
    cout<<"j2 : \n"<<j2;
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



Note& Note::fromJson(json j){
    Note* n = new Note(QString::fromStdString(j["id"]), QString::fromStdString(j["title"]), dateFromQString(QString::fromStdString(j["dateCreation"])), dateFromQString(QString::fromStdString(j["dateLastUpdate"])), j["noteStatus"]);
    return *n;
}

Article& Article::fromJson(json j){
    Article* a = new Article(QString::fromStdString(j["id"]), QString::fromStdString(j["title"]), dateFromQString(QString::fromStdString(j["dateCreation"])), dateFromQString(QString::fromStdString(j["dateLastUpdate"])), j["noteStatus"], QString::fromStdString(j["text"]));
    return *a;
}

Task& Task::fromJson(json j){
    Task* t = new Task(QString::fromStdString(j["id"]), QString::fromStdString(j["title"]), dateFromQString(QString::fromStdString(j["dateCreation"])), dateFromQString(QString::fromStdString(j["dateLastUpdate"])), j["noteStatus"], QString::fromStdString(j["action"])/*, j["taskStatus"]*/);
    return *t;
}

TaskWithPriority& TaskWithPriority::fromJson(json j){

//    TaskWithPriority* twp = new TaskWithPriority(QString::fromStdString(j["id"]), QString::fromStdString(j["title"]), dateFromQString(QString::fromStdString(j["dateCreation"])), dateFromQString(QString::fromStdString(j["dateLastUpdate"])), j["noteStatus"], QString::fromStdString(j["action"]), waiting, j["priority"]);
//    Task& t = Task::fromJson(j);
    TaskWithPriority* twp = new TaskWithPriority(t.getIdentifier(), t.getTitle(), t.getDateCreation(), t.getDateLastUpdate(), t.getNoteStatus(), t.getAction(), t.getStatus(), (int)j["priority"]);
    return *twp;
}

TaskWithDeadline& TaskWithDeadline::fromJson(json j){
    Task& t = Task::fromJson(j);
    TaskWithDeadline* twd = new TaskWithDeadline(t.getIdentifier(), t.getTitle(), t.getDateCreation(), t.getDateLastUpdate(), t.getNoteStatus(), t.getAction(), t.getStatus(), Note::dateFromQString(QString::fromStdString(j["deadline"])));
    return *twd;
}

OtherNote& OtherNote::fromJson(json j){
    OtherNote* t = new OtherNote(QString::fromStdString(j["id"]), QString::fromStdString(j["title"]), dateFromQString(QString::fromStdString(j["dateCreation"])), dateFromQString(QString::fromStdString(j["dateLastUpdate"])), j["noteStatus"], QString::fromStdString(j["description"]), QString::fromStdString(j["fileName"]), j["type"]);
    return *t;
}


NoteVersions &NoteVersions::fromJson(json j){
    NoteVersions * NV = new NoteVersions;
    NV->type = j["type"];
    json j2 = j["Versions"];
    cout<<"-------------------"<<endl
        <<"Versions : "<<endl
        <<j2<<endl
        <<"-------------------"<<endl;
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
        cout<<*NV;
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
    cout<<"debug2"<<endl;
    cout<<directory.toStdString()+"plurinotes.json"<<endl;
    if(file.good()!=true){
        QString message;
        message.fromStdString(directory.toStdString()+"plurinotes.json was not found");
        throw NotesException(message);
    }
    json j;
    file >> j;
    file.close();
    json j2 = j["NoteVersions"];
    for (json::iterator it = j2.begin() ; it != j2.end() ; ++it){
        //cout<<"Noteversion : "<<NoteVersions::fromJson(*it)<<endl;
        addNoteVersion(&NoteVersions::fromJson(*it));
    }
    cout<<"NM : \n"<<*this;
}


