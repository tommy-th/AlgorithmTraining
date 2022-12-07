#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <unordered_map>

using namespace std;

struct Box;
using BoxPtr = Box *;

int Q, N, M;
int brokenBelts[11] = {0,};
vector<BoxPtr> belts = vector<BoxPtr>(11, nullptr);

vector<shared_ptr<Box>> boxes;
unordered_map<int, BoxPtr> boxMap;

struct Box {
  int id;
  int beltId;
  int weight;
  BoxPtr prev = nullptr;
  BoxPtr next = nullptr;

  Box(int i, int bi, int w) {
    id = i;
    beltId = bi;
    weight = w;
  }

  int getOff(const int maxWeight) {
    belts[beltId] = next;
    if (weight > maxWeight) {
      return 0;
    }

    if (id == next->id) {
      belts[beltId] = nullptr;
    } else {
      next->prev = prev;
      prev->next = next;
    }
    boxMap.erase(id);

    return weight;
  }

  int remove() {
    next->prev = prev;
    prev->next = next;

    if (id == belts[beltId]->id) {
      if (id == next->id) {
        belts[beltId] = nullptr;
      } else {
        belts[beltId] = next;
      }
    }
    boxMap.erase(id);

    return id;
  }

  int check() {
    belts[beltId] = this;
    return beltId + 1;
  }

  int changeBelt(const int nBeltId) {
    if (belts[nBeltId] == nullptr) {
      belts[nBeltId] = this;
    } else {
      BoxPtr start = belts[nBeltId];
      BoxPtr mid1 = belts[nBeltId]->prev;
      BoxPtr mid2 = this;
      BoxPtr end = prev;

      start->prev = end;
      end->next = belts[nBeltId];
      mid1->next = mid2;
      mid2->prev = mid1;
    }

    BoxPtr cur = this;
    int pBeltId = beltId;
    while (cur->beltId == pBeltId) {
      cur->beltId = nBeltId;
      cur = cur->next;
    }
    belts[pBeltId] = nullptr;
    return pBeltId + 1;
  }
};

enum class Command : int {
  CONSTRUCT = 100,
  GET_OFF = 200,
  REMOVE_BOX = 300,
  CHECK_BOX = 400,
  BELT_ERROR = 500,
};

void processConstruct() {
  int id, weight;
  vector<int> boxIds = vector<int>();
  vector<int> weights = vector<int>();

  cin >> N >> M;
  int chunkSize = N / M;
  for (int i = 0; i < N; ++i) {
    cin >> id;
    boxIds.push_back(id);
  }
  for (int i = 0; i < N; ++i) {
    cin >> weight;
    weights.push_back(weight);
  }

  for (int i = 0; i < N; ++i) {
    int beltId = i / chunkSize;
    shared_ptr<Box> newBox = make_shared<Box>(boxIds[i], beltId, weights[i]);
    boxes.push_back(newBox);
    boxMap.insert(make_pair(newBox->id, newBox.get()));

    if (belts[beltId] == nullptr) {
      newBox->prev = newBox.get();
      newBox->next = newBox.get();
      belts[beltId] = newBox.get();
    } else {
      newBox->prev = belts[beltId]->prev;
      newBox->next = belts[beltId];

      belts[beltId]->prev->next = newBox.get();
      belts[beltId]->prev = newBox.get();
    }
  }
}

void processGetOff() {
  int weightMax;
  cin >> weightMax;

  int weightSum = 0;
  for (int beltId = 0; beltId < M; ++beltId) {
    BoxPtr box = belts[beltId];
    if (box != nullptr) {
      weightSum += box->getOff(weightMax);
    }
  }

  cout << weightSum << endl;
}

void processRemoveBox() {
  int boxId;
  cin >> boxId;

  auto findIter = boxMap.find(boxId);
  if (findIter == boxMap.end()) {
    cout << "-1" << endl;
  } else {
    BoxPtr box = findIter->second;
    cout << box->remove() << endl;
  }
}

void processCheckBox() {
  int boxId;
  cin >> boxId;

  auto findIter = boxMap.find(boxId);
  if (findIter == boxMap.end()) {
    cout << "-1" << endl;
  } else {
    BoxPtr box = findIter->second;
    cout << box->check() << endl;
  }
}

void processBeltError() {
  int beltId, nBeltId = 0;
  cin >> beltId;
  beltId -= 1;

  if (brokenBelts[beltId]) {
    cout << "-1" << endl;
    return;
  }
  brokenBelts[beltId] = 1;

  for (int i = 1; i < M; ++i) {
    nBeltId = (beltId + i) % M;
    if (brokenBelts[nBeltId] == 0)
      break;
  }

  BoxPtr box = belts[beltId];
  if (box == nullptr) {
    cout << beltId + 1 << endl;
  } else {
    cout << box->changeBelt(nBeltId) << endl;
  }

}

void process(const Command &command) {
  switch (command) {
    case Command::CONSTRUCT:return processConstruct();
    case Command::GET_OFF:return processGetOff();
    case Command::REMOVE_BOX:return processRemoveBox();
    case Command::CHECK_BOX:return processCheckBox();
    case Command::BELT_ERROR:return processBeltError();
    default:break;
  }
}

int main() {
  int commandCode;

  cin >> Q;
  for (int i = 0; i < Q; ++i) {
    cin >> commandCode;
    const auto command = static_cast<Command>(commandCode);
    process(command);
  }

  return 0;
}
