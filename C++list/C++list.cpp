// C++list.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream> 
#include <list> 

using namespace std;

int main()
{
    // 리스트 생성 
    list<int> a;

    // 원소 추가 
    a.push_back(22);
    a.push_back(33);
    a.push_front(11);
    a.push_back(44);
    a.push_back(55);

    // 반복자 생성 
    list<int>::iterator iter = a.begin();

    // 리스트 출력 
    for (iter = a.begin(); iter != a.end(); iter++)
    {
        cout << *iter << endl; // 원본 리스트: 11 22 33 44 55 
    }

    cout << "" << endl;
    cout << "" << endl;

    // 원소 삭제 
    a.pop_front();
    a.pop_back();

    for (iter = a.begin(); iter != a.end(); iter++)
    {
        cout << *iter << endl; // 원소 삭제후 리스트: 22 33 44 
    }

    cout << "" << endl;

    // 리스트 사이즈 출력 
    cout << a.size() << endl; // 3 출력( 22, 33, 44 이므로) 

    // 리스트가 비어있는가 
    cout << a.empty() << endl; // 비어있지 않으므로 0 반환 

    // 리스트 첫번째 원소 출력 
    cout << a.front() << endl; // 22 

    // 리스트 마지막 원소 출력 
    cout << a.back() << endl; // 44 

    cout << "" << endl;
    iter = a.begin();

    // 반복자 2번째 위치로 이동 
    iter++; // 반복자가 두번째 원소(33)를 가리킴 
    iter++; // 반복자가 세번째 원소(44)를 가리킴 
    a.insert(iter, 55555);
    for (iter = a.begin(); iter != a.end(); iter++)
    {
        cout << *iter << endl; //세번째 원소(44) 전에 추가하는 것(22,55555,33,44) 
    }
}


// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.
