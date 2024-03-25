#include <cstdint>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

class FileSystem {
   public:
    class dual_name_id_map {
       public:
        struct NameFindResult {
            std::unordered_map<std::string_view, uint64_t>::iterator iter;
            std::unordered_map<std::string_view, uint64_t>::iterator end;
        };
        struct IdFindResult {
            std::unordered_map<uint64_t, std::string>::iterator iter;
            std::unordered_map<uint64_t, std::string>::iterator end;
        };

        void insert(const std::string name, const uint64_t id) {
            const std::string_view nameView =
                this->idToNameView.emplace(id, move(name)).first->second;
            this->nameToId.emplace(nameView, id);
        }

        void eraseWithName(const std::string_view name) {
            auto iter = this->nameToId.find(name);
            uint64_t id = iter->second;
            this->idToNameView.erase(id);
            this->nameToId.erase(iter);
        }

        void eraseWithId(const uint64_t id) {
            auto iter = this->idToNameView.find(id);
            this->nameToId.erase(iter->second);
            this->idToNameView.erase(iter);
        }

        bool countWithName(const std::string_view name) const {
            return this->nameToId.count(name);
        }

        bool countWithId(const uint64_t id) const {
            return this->idToNameView.count(id);
        }

        NameFindResult findWithName(const std::string_view name) {
            return {
                .iter = this->nameToId.find(name),
                .end = this->nameToId.end(),
            };
        }

        IdFindResult findWithId(const uint64_t id) {
            return {
                .iter = this->idToNameView.find(id),
                .end = this->idToNameView.end(),
            };
        }

        uint64_t getIdWithName(const std::string_view name) const {
            return this->nameToId.at(name);
        }

        const std::string_view getNameWithId(const uint64_t id) const {
            return this->idToNameView.at(id);
        }

        const std::unordered_map<uint64_t, std::string> getIdToNameView() const {
            return this->idToNameView;
        }

        const std::unordered_map<std::string_view, uint64_t> getNameToId() const {
            return this->nameToId;
        }

       private:
        std::unordered_map<std::string_view, uint64_t> nameToId;
        std::unordered_map<uint64_t, std::string> idToNameView;
    };

    struct FolderContents {
        FileSystem::dual_name_id_map
            folderMap;

        FileSystem::dual_name_id_map dashboardMap;
        FileSystem::dual_name_id_map worksheetMap;
    };

    FileSystem() {
        this->totalDashboardCount = 0;
        this->totalWorksheetCount = 0;

        this->creationTime = std::time(0);

        auto tm = std::gmtime(&this->creationTime);
        std::ostringstream oss;
        oss << std::put_time(tm, "%d-%m-%Y %H-%M-%S");
        this->creationId = this->fileSystemHash(oss.str());

        this->rootFolderId =
            this->fileSystemFileHash(this->creationId, "MyDocuments");

        this->allFoldersMap.emplace(this->rootFolderId, FolderContents{});
        this->allFilesIdNameMap.insert("MyDocments", this->rootFolderId);
        this->allFilesTypeAndContainerMap.emplace(
            this->rootFolderId, std::pair<uint64_t, char>(UINT64_MAX, 'f'));

        std::cout << "FileSystem instance " << creationId
                  << ":: A new instance of FileSystem has been created with a "
                     "\"MyDocuments\" root folder. This root folder has the "
                     "following folder id value: "
                  << this->rootFolderId << std::endl;
    }

    size_t getTotalDashboards() const { return this->totalDashboardCount; }

    size_t getTotalWorksheets() const { return this->totalWorksheetCount; }

    uint64_t addNewFile(const std::string fileName, const std::string fileType,
                        uint64_t folderId) {
        if (fileType != "dashboard" && fileType != "worksheet" &&
            fileType != "folder" && fileType != "d" && fileType != "w" &&
            fileType != "f") {
            std::cout << "FileSystem instance " << creationId
                      << "::addNewFile(feilName, fileType, folderId):: the passed "
                         "`fileType` value does not represent a valid "
                         "file type for this system. Below are your file type options"
                      << std::endl;
            std::cout << "\tdashboard" << std::endl;
            std::cout << "\tworksheet" << std::endl;
            std::cout << "\tfolder" << std::endl;
            return 0;
        }

        if (folderId == 0) {
            folderId = this->rootFolderId;
        }

        auto iterAtFolderId = this->allFoldersMap.find(folderId);
        if (iterAtFolderId == this->allFoldersMap.end()) {
            std::cout << "FileSystem instance " << creationId
                      << "::addNewFile(feilName, fileType, folderId):: the passed "
                         "`folderId` value does not represent a folder "
                         "currently within the system."
                      << std::endl;
            return 0;
        }

        if (iterAtFolderId->second.dashboardMap.countWithName(fileName) ||
            iterAtFolderId->second.worksheetMap.countWithName(fileName) ||
            iterAtFolderId->second.folderMap.countWithName(fileName)) {
            std::cout << "FileSystem instance " << creationId
                      << "::addNewFile(feilName, fileType, folderId):: the folder "
                         "represented by the `folderId` value already "
                         "contains a file with a name equal to the passed "
                         "`fileName`, please enter a different value for either the "
                         "`folderId` parameter or the `fileName` parameter."
                      << std::endl;
            std::cout << "\tfolderId: " << folderId << std::endl;
            std::cout << "\tfileName: " << fileName << std::endl;
            return 0;
        }

        uint64_t newFileHash = this->fileSystemFileHash(folderId, fileName);

        if (folderId != 0 &&
            this->allFilesIdNameMap.countWithId(newFileHash) == true) {
            std::cout
                << "FileSystem instance " << creationId
                << "::addNewFile(feilName, fileType, folderId):: the passed "
                   "`folderId` and `fileName` combination have "
                   "produced a new folder id that is already present within this "
                   "file-system, please enter a different value for either the "
                   "`folderId` parameter or the `fileName` parameter."
                << std::endl;
            std::cout << "\tTip: note that this error is different from the \"file "
                         "name is already present in the passed containing folder\" "
                         "error. This error stems from the hashing algorithm for "
                         "FileSystem instances producing collisions for folder ids."
                      << std::endl;
            return 0;
        }

        switch (fileType[0]) {
            case 'd': {
                ++this->totalDashboardCount;
                iterAtFolderId->second.dashboardMap.insert(fileName, newFileHash);

                std::cout << "FileSystem instance " << creationId
                          << "::addNewFile(feilName, fileType, folderId):: A new "
                             "dashboard has been created with the following metadata:"
                          << std::endl;
                break;
            }
            case 'w': {
                ++this->totalWorksheetCount;
                iterAtFolderId->second.worksheetMap.insert(fileName, newFileHash);

                std::cout << "FileSystem instance " << creationId
                          << "::addNewFile(feilName, fileType, folderId):: A new "
                             "worksheet has been created with the following metadata:"
                          << std::endl;
                break;
            }
            case 'f': {
                uint64_t newFileHash = this->fileSystemFileHash(folderId, fileName);

                this->allFoldersMap.emplace(newFileHash, FolderContents{});
                iterAtFolderId->second.folderMap.insert(fileName, newFileHash);

                std::cout << "FileSystem instance " << creationId
                          << "::addNewFile(feilName, fileType, folderId):: A new folder "
                             "has been created with the following metadata:"
                          << std::endl;
                break;
            }
        }

        std::cout << "\tname: " << fileName << std::endl;
        std::cout << "\tid: " << newFileHash << std::endl;

        this->allFilesIdNameMap.insert(fileName, newFileHash);
        this->allFilesTypeAndContainerMap.emplace(
            newFileHash, std::pair<uint64_t, char>(folderId, fileType[0]));

        return newFileHash;
    }

    uint64_t getFileId(const std::string fileName, uint64_t folderId) const {
        if (fileName == "MyDocuments") {
            return this->rootFolderId;
        } else if (folderId == 0) {
            folderId = this->rootFolderId;
        }

        auto iterInAllFoldersMap = this->allFoldersMap.find(folderId);
        if (iterInAllFoldersMap == this->allFoldersMap.end()) {
            std::cout << "FileSystem instance " << creationId
                      << "::getFileId(fileName, folderID):: the passed `folderId` "
                         "value does not represent a folder "
                         "currently within the system."
                      << std::endl;
            std::cout << "\tfolderId: " << folderId << std::endl;
            return 0;
        }

        if (iterInAllFoldersMap->second.dashboardMap.countWithName(fileName)) {
            return iterInAllFoldersMap->second.dashboardMap.getIdWithName(fileName);
        }

        if (iterInAllFoldersMap->second.worksheetMap.countWithName(fileName)) {
            return iterInAllFoldersMap->second.worksheetMap.getIdWithName(fileName);
        }

        if (iterInAllFoldersMap->second.folderMap.countWithName(fileName)) {
            return iterInAllFoldersMap->second.folderMap.getIdWithName(fileName);
        }

        std::cout << "FileSystem instance " << creationId
                  << "::getFileId(fileName, folderID):: the folder represented by "
                     "the `folderId` value does not "
                     "contain a file with a name equal to the passed `fileName` "
                     "parameter, please try a different value for either the "
                     "`folderId` parameter or the `fileName` parameter."
                  << std::endl;
        std::cout << "\tfolderId: " << folderId << std::endl;
        std::cout << "\tfileName: " << fileName << std::endl;
        return 0;
    }

    void moveFile(const uint64_t fileId, uint64_t newFolderId) {
        if (newFolderId == 0) {
            newFolderId = this->rootFolderId;
        }

        if (fileId == 0 || fileId == this->rootFolderId) {
            std::cout << "FileSystem instance " << creationId
                      << "::moveFile(fileId, newFolderId):: the passed `fileId` "
                         "value represents the root folder of this FileSystem "
                         "instance. You are not allowed to move the root folder."
                      << std::endl;
            std::cout << "\tfileId: " << fileId << std::endl;
        }

        auto ItertoFileTypeCont = this->allFilesTypeAndContainerMap.find(fileId);
        if (ItertoFileTypeCont == this->allFilesTypeAndContainerMap.end()) {
            std::cout << "FileSystem instance " << creationId
                      << "::moveFile(fileId, newFolderId):: the passed `fileId` "
                         "value does not represent a file "
                         "currently within the system."
                      << std::endl;
            std::cout << "\tfileId: " << fileId << std::endl;
            return;
        }

        auto IterAtNewFolder = this->allFoldersMap.find(newFolderId);
        if (IterAtNewFolder == this->allFoldersMap.end()) {
            std::cout << "FileSystem instance " << creationId
                      << "::moveFile(fileId, newFolderId):: the passed `newFolderId` "
                         "value does not represent a folder "
                         "currently within the system."
                      << std::endl;
            return;
        } else if (IterAtNewFolder->second.dashboardMap.countWithId(fileId) ||
                   IterAtNewFolder->second.worksheetMap.countWithId(fileId) ||
                   IterAtNewFolder->second.folderMap.countWithId(fileId)) {
            std::cout << "FileSystem instance " << creationId
                      << "::moveFile(fileId, newFolderId):: the folder represented "
                         "by the `newFolderId` value already "
                         "contains a file with a name equal to the passed "
                         "`fileName`, please enter a different value for either the "
                         "`folderId` parameter or the `fileName` parameter."
                      << std::endl;
            return;
        }

        FolderContents &oldFolderContents =
            this->allFoldersMap.find(ItertoFileTypeCont->second.first)->second;
        FolderContents &newFolderContents = IterAtNewFolder->second;
        std::string fileName =
            this->allFilesIdNameMap.findWithId(ItertoFileTypeCont->second.first)
                .iter->second;
        char fileType = ItertoFileTypeCont->second.second;

        switch (fileType) {
            case 'd': {
                oldFolderContents.dashboardMap.eraseWithId(fileId);
                newFolderContents.dashboardMap.insert(fileName, fileId);
                break;
            }
            case 'w': {
                oldFolderContents.worksheetMap.eraseWithId(fileId);
                newFolderContents.worksheetMap.insert(fileName, fileId);
                break;
            }
            case 'f': {
                oldFolderContents.folderMap.eraseWithId(fileId);
                newFolderContents.folderMap.insert(fileName, fileId);
                break;
            }
        }

        ItertoFileTypeCont->second.first = IterAtNewFolder->first;

        return;
    }

    std::vector<std::string> getFiles(uint64_t folderId) const {
        if (folderId == 0) {
            folderId = this->rootFolderId;
        }
        auto IterAtFolder = this->allFoldersMap.find(folderId);
        if (IterAtFolder == this->allFoldersMap.end()) {
            std::cout << "FileSystem instance " << creationId
                      << "::getFiles(folderId):: the passed `folderId` value does "
                         "not represent a folder "
                         "currently within the system."
                      << std::endl;
            return {};
        }

        std::vector<std::string> ans;
        for (auto &ele : IterAtFolder->second.dashboardMap.getIdToNameView()) {
            ans.push_back(ele.second);
        }
        for (auto &ele : IterAtFolder->second.worksheetMap.getIdToNameView()) {
            ans.push_back(ele.second);
        }
        for (auto &ele : IterAtFolder->second.folderMap.getIdToNameView()) {
            ans.push_back(ele.second);
        }

        return ans;
    }

    void printFiles() const {
        std::unordered_set<uint64_t> notVisited;
        for (auto &ele : this->allFilesTypeAndContainerMap) {
            notVisited.insert(ele.first);
        }
        std::stack<std::pair<int, uint64_t>> folderStack;
        folderStack.push({0, this->rootFolderId});

        while (folderStack.empty() == false) {
            uint64_t node =
                folderStack.top().second;
            int depth = folderStack.top().first;
            folderStack.pop();

            if (notVisited.count(node) == true) {
                notVisited.erase(node);
                char fileType = this->allFilesTypeAndContainerMap.at(node).second;
                std::cout << std::string(depth, '\t') << fileType << ' ' << node << ' '
                          << this->allFilesIdNameMap.getNameWithId(node)
                          << std::endl;
                if (fileType != 'f') {
                    continue;
                }
                for (auto &neighbor :
                     this->allFoldersMap.at(node).dashboardMap.getIdToNameView()) {
                    std::cout << std::string(depth, '\t') << "d " << neighbor.first << ' '
                              << this->allFilesIdNameMap.getNameWithId(neighbor.first)
                              << std::endl;
                }
                for (auto &neighbor :
                     this->allFoldersMap.at(node).worksheetMap.getIdToNameView()) {
                    std::cout << std::string(depth, '\t') << "w " << neighbor.first << ' '
                              << this->allFilesIdNameMap.getNameWithId(neighbor.first)
                              << std::endl;
                }

                for (auto &neighbor :
                     this->allFoldersMap.at(node).folderMap.getIdToNameView()) {
                    if (notVisited.count(neighbor.first) == true) {
                        folderStack.push({depth + 1, neighbor.first});
                    }
                }
            }
        }
    }

   private:
    uint64_t rootFolderId;
    uint64_t creationId;
    std::time_t creationTime;
    size_t totalDashboardCount;
    size_t totalWorksheetCount;

    const uint64_t fileSystemHash(const std::string_view name) {
        uint64_t res = std::hash<std::string_view>{}(name);
        return res % 2 == 0 ? res : res + 1;
    }
    const uint64_t fileSystemFileHash(const uint64_t containingFolderId,
                                      const std::string_view folderName) {
        uint64_t res = std::hash<std::string>{}(
            std::to_string(containingFolderId).append(folderName));
        return res % 2 == 0 ? res : res + 1;
    }

    std::unordered_map<uint64_t, FolderContents> allFoldersMap;

    FileSystem::dual_name_id_map allFilesIdNameMap;

    std::unordered_map<uint64_t, std::pair<uint64_t, char>>
        allFilesTypeAndContainerMap;
};

/////////////////////////////////////////////////////////
// YOU DO NOT NEED TO MAKE CHANGES BELOW UNLESS NECESSARY
/////////////////////////////////////////////////////////

void printCommaSeparated(std::vector<std::string> strings) {
    for (size_t i = 0; i < strings.size(); i++) {
        if (i > 0) {
            printf(", ");
        }
        printf("%s", strings[i].c_str());
    }
    printf("\n");
}

// PLEASE ENSURE runExample() COMPILES AND RUNS BEFORE SUBMITTING.
void runExample() {
    FileSystem *fs = new FileSystem();
    uint64_t rootId = fs->getFileId("MyDocuments", 0);
    fs->addNewFile("draft", "folder", rootId);
    fs->addNewFile("complete", "folder", rootId);
    uint64_t draftId = fs->getFileId("draft", rootId);
    uint64_t completeId = fs->getFileId("complete", rootId);
    fs->addNewFile("foo", "worksheet", draftId);
    fs->addNewFile("bar", "dashboard", completeId);
    uint64_t fooId = fs->getFileId("foo", draftId);
    fs->moveFile(fooId, completeId);

    printCommaSeparated(fs->getFiles(rootId));
    printCommaSeparated(fs->getFiles(draftId));
    printCommaSeparated(fs->getFiles(completeId));

    fs->addNewFile("project", "folder", draftId);
    uint64_t projectId = fs->getFileId("project", draftId);
    fs->addNewFile("page1", "worksheet", projectId);
    fs->addNewFile("page2", "worksheet", projectId);
    fs->addNewFile("page3", "worksheet", projectId);
    fs->addNewFile("cover", "dashboard", projectId);
    fs->moveFile(projectId, completeId);
    projectId = fs->getFileId("project", completeId);
    uint64_t coverId = fs->getFileId("cover", projectId);
    fs->moveFile(coverId, rootId);

    printCommaSeparated(fs->getFiles(rootId));
    printCommaSeparated(fs->getFiles(draftId));
    printCommaSeparated(fs->getFiles(completeId));
    printCommaSeparated(fs->getFiles(projectId));

    printf("%d\n", fs->getTotalDashboards());
    printf("%d\n", fs->getTotalWorksheets());
    fs->printFiles();
}

#define MENU                                  \
    "\n"                                      \
    "Enter an integer to indicate a command:" \
    "\n"                                      \
    "[1] getTotalDashboards"                  \
    "\n"                                      \
    "[2] getTotalWorksheets"                  \
    "\n"                                      \
    "[3] addNewFile"                          \
    "\n"                                      \
    "[4] getFileId"                           \
    "\n"                                      \
    "[5] moveFile"                            \
    "\n"                                      \
    "[6] gettFiles"                           \
    "\n"                                      \
    "[7] printFiles"                          \
    "\n"                                      \
    "[8] exit"                                \
    "\n"                                      \
    "\n"

#define OUT_COUNT_DASHBOARDS                      \
    "There are %d dashboards in the file system." \
    "\n"

#define OUT_COUNT_WORKSHEETS                      \
    "There are %d worksheets in the file system." \
    "\n"

#define IN_NEW_FILE_1        \
    "Enter a new file name:" \
    "\n"
#define IN_NEW_FILE_2                                      \
    "Enter a file type (worksheet, dashboard, or folder):" \
    "\n"
#define IN_NEW_FILE_3                                      \
    "Enter a folder id where you'd like to put this file:" \
    "\n"
#define OUT_NEW_FILE                  \
    "%s has been added to folder %d." \
    "\n"

#define IN_CREATION_TIME_1 \
    "Enter a file name:"   \
    "\n"
#define IN_CREATION_TIME_2 \
    "Enter a folder id:"   \
    "\n"
#define OUT_CREATION_TIME \
    "%s is file %d."      \
    "\n"

#define IN_MOVE_FILE_1 \
    "Enter a file id:" \
    "\n"
#define IN_MOVE_FILE_2                                        \
    "Enter the folder id where you'd like to move this file:" \
    "\n"
#define OUT_MOVE_FILE                          \
    "Successfully moved file %d to folder %d." \
    "\n"

#define IN_GET_FILES     \
    "Enter a folder id:" \
    "\n"
#define OUT_GET_FILES_1               \
    "There are no files in folder %d" \
    "\n"
#define OUT_GET_FILES_2                     \
    "The following files are in folder %d:" \
    "\n"

#define EXIT           \
    "Exiting program." \
    "\n"
#define INVALID_CMD                          \
    "Invalid command: %d. Please try again." \
    "\n"

void askQuestion() {
    FileSystem *fs = new FileSystem();
    bool running = true;
    unsigned short command;

    while (running) {
        printf(MENU);
        std::cin >> command;

        switch (command) {
            case 1: {
                printf(OUT_COUNT_DASHBOARDS, fs->getTotalDashboards());
                break;
            }
            case 2: {
                printf(OUT_COUNT_WORKSHEETS, fs->getTotalWorksheets());
                break;
            }
            case 3: {
                std::string fileName, fileType;
                uint64_t folderId;
                printf(IN_NEW_FILE_1);
                std::cin >> fileName;
                printf(IN_NEW_FILE_2);
                std::cin >> fileType;
                printf(IN_NEW_FILE_3);
                std::cin >> folderId;
                fs->addNewFile(fileName, fileType, folderId);
                printf(OUT_NEW_FILE, fileName.c_str(), folderId);
                break;
            }
            case 4: {
                std::string fileName;
                uint64_t folderId;
                printf(IN_CREATION_TIME_1);
                std::cin >> fileName;
                printf(IN_CREATION_TIME_2);
                std::cin >> folderId;
                printf(OUT_CREATION_TIME, fileName.c_str(),
                       fs->getFileId(fileName, folderId));
                break;
            }
            case 5: {
                uint64_t fileId, newFolderId;
                printf(IN_MOVE_FILE_1);
                std::cin >> fileId;
                printf(IN_MOVE_FILE_2);
                std::cin >> newFolderId;
                fs->moveFile(fileId, newFolderId);
                printf(OUT_MOVE_FILE, fileId, newFolderId);
                break;
            }
            case 6: {
                uint64_t folderId;
                printf(IN_GET_FILES);
                std::cin >> folderId;
                auto fileNames = fs->getFiles(folderId);
                if (fileNames.size() == 0) {
                    printf(OUT_GET_FILES_1, folderId);
                } else {
                    printf(OUT_GET_FILES_2, folderId);
                    for (auto it = fileNames.begin(); it != fileNames.end(); ++it) {
                        printf("\t%s\n", it->c_str());
                    }
                }
                break;
            }
            case 7: {
                fs->printFiles();
                break;
            }
            case 8: {
                printf(EXIT);
                running = false;
                break;
            }
            default: {
                printf(INVALID_CMD, command);
                break;
            }
        }
    }

    delete fs;
}

// int main() {
//     printf(
//         "runExample output:"
//         "\n");
//     runExample();
//     printf("\n");
//     printf(
//         "askQuestion output:"
//         "\n");
//     askQuestion();
// }