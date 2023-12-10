#include <iostream>
#include <string>
#include <cmath>
#include <limits>
#include <fstream>
#include <cstdlib>
#include <cwchar>
#include <locale>
#include <codecvt>
#include <sstream>
#include <fstream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <set>
#include "base_map.pb.h"
#include "geometry.pb.h"
#include "kdTree.h"
#include "kdTreeNode.h"
using namespace std;

//接收一个map对象，也就是base_map.bin
void Road(const apollo::hdmap::Map &map) {
    cout << "Found " << map.junction_size() << " junctions in base_map.bin" << endl;
    //从messasge Map中找junction那一堆，并用junction的数量作为循环，
    // 其中junction_size()这个函数是protobuf在.cc文件中自动生成的，直接调用即可
    for (int i = 0; i < map.junction_size(); i++) {
        //建立一个junction对象
        const apollo::hdmap::Junction &junction = map.junction(i);
        //分别输出每个junction的id值，其中第一个.id()表示找到junction模块中的Id模块，
        // 第二个.id()表示选择Id模块中的id值进行输出
        cout << "Junction ID: " << junction.id().id() << endl;
        for (int j = 0; j < junction.polygon().point_size(); j++) {
            cout << "x:" << junction.polygon().point(j).x();
            cout << " y:" << junction.polygon().point(j).y();
            cout << " z:" << junction.polygon().point(j).z() << endl;
            }
            cout << endl;
    }
}

// Main function:  Reads the entire address book from a file and prints all
//   the information  inside.
int main(int argc, char *argv[]) {
    // Verify that the version of the library that we linked against is
    // compatible with the version of the headers we compiled against.
    GOOGLE_PROTOBUF_VERIFY_VERSION;
    //确认文件是否正确
    if (argc != 3) {
        cerr << "Usage:  " << argv[0] << " base_map.bin routing_map.bin" << endl;
        return -1;
    }

    apollo::hdmap::Map map;
    apollo::hdmap::RoutingMap routing_map;

    {
        // Read base_map.bin
        fstream catch_sapce(argv[1], ios::in | ios::binary);
        if (!map.ParseFromIstream(&catch_sapce)) {
            cerr << "Failed to parse base map." << endl;
            return -1;
        }
    }
    {
        // Read routing_map.bin
        fstream routing_map_file(argv[2], ios::in | ios::binary);
        if (!routing_map.ParseFromIstream(&routing_map_file)) {
            cerr << "Failed to parse routing map." << endl;
            return -1;
        }
    }

    Road(map);

    // Optional:  Delete all global objects allocated by libprotobuf.
    google::protobuf::ShutdownProtobufLibrary();
    
    kdTree *mykdTree = new kdTree();
    kdTreeNode *node;
    for (int i = 0; i < map.lane_size(); i++) {
        const apollo::hdmap::Lane &lane = map.lane(i);
        //central_curve
        for (int j = 0; j < lane.central_curve().segment(0).line_segment().point_size(); j++) {
            node = new kdTreeNode(lane.central_curve().segment(0).line_segment().point(j).x(),
                                  lane.central_curve().segment(0).line_segment().point(j).y());
            node->setLane_id(lane.id().id()); // 设置该点所属的lane_id
            mykdTree->insert(node);
        }
        //start_position
        node = new kdTreeNode(lane.central_curve().segment(0).start_position().x(),
                              lane.central_curve().segment(0).start_position().y());
        node->setLane_id(lane.id().id()); // 设置该点所属的lane_id
        mykdTree->insert(node);
        //left_boundary
        for (int j = 0; j < lane.left_boundary().curve().segment(0).line_segment().point_size(); j++) {
            node = new kdTreeNode(lane.left_boundary().curve().segment(0).line_segment().point(j).x(),
                                  lane.left_boundary().curve().segment(0).line_segment().point(j).y());
            node->setLane_id(lane.id().id()); // 设置该点所属的lane_id
            mykdTree->insert(node);
        }
        //right_boundary
        for (int j = 0; j < lane.right_boundary().curve().segment(0).line_segment().point_size(); j++) {
            node = new kdTreeNode(lane.right_boundary().curve().segment(0).line_segment().point(j).x(),
                                  lane.right_boundary().curve().segment(0).line_segment().point(j).y());
            node->setLane_id(lane.id().id()); // 设置该点所属的lane_id
            mykdTree->insert(node);
        }
    }
    double x, y;
    cout << "please enter coordinates: ";
    cin >> x >> y;
    kdTreeNode *startNode = new kdTreeNode(x, y);
    cout << "the start node is: (" << startNode->getX() << " " << startNode->getY() << ")" << endl;
    kdTreeNode *closestNodeToStart;
    closestNodeToStart = mykdTree->findClosestPoint(startNode);
    cout << "the nearest node to the start point is: (" << closestNodeToStart->getX() << ", " << closestNodeToStart->getY() << ")" << endl;
    cout << "the nearest node's lane id is: " << closestNodeToStart->getLane_id() << endl; // 输出最近点所属的lane_id
    //print the first road
    std::string base = "imap -m base_map.txt -l ";
    base += closestNode->getLane_id();
    system(base.c_str());
    
    return 0;
}
