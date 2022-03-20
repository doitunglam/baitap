#include <bits/stdc++.h>

using namespace std;

void printVector(vector<int> tar)
{
    for (int i = 0; i < tar.size(); i++)
        cout << tar[i] << " ";
}
vector<int> strassenAlgorithm(vector<int> polyA, vector<int> polyB)
{
    vector<int> polynomialA, polynomialB;
    if (polyA.size() < polyB.size())
    {
        polynomialA = polyB;
        polynomialB = polyA;
    }
    else
    {
        polynomialA = polyA;
        polynomialB = polyB;
    }
    // Pre-declare
    if (polynomialB.size() == 1)
    {
        for (int i = 0; i < polynomialA.size(); i++)
            polynomialA[i] *= polynomialB[0];
        return polynomialA;
    }
    if (polynomialB.size() == 0)
        return polynomialB;
    size_t halfMaxSize = polynomialA.size() / 2;
    vector<int> polynomialAFirstHalf(polynomialA.begin(), polynomialA.begin() + halfMaxSize);
    vector<int> polynomialASecondHalf(polynomialA.begin() + halfMaxSize, polynomialA.end());
    vector<int> polynomialBFirstHalf, polynomialBSecondHalf;
    if (halfMaxSize < polynomialB.size())
    {
        vector<int> dummy1(polynomialB.begin(), polynomialB.begin() + halfMaxSize);
        vector<int> dummy2(polynomialB.begin() + halfMaxSize, polynomialB.end());
        polynomialBFirstHalf = dummy1;
        polynomialBSecondHalf = dummy2;
    }
    else
        polynomialBFirstHalf = polynomialB;
    //(P+Qx)(R+Sx)=PR+(QR+PS)x+QSx^2
    vector<int> PR = strassenAlgorithm(polynomialAFirstHalf, polynomialBFirstHalf);
    vector<int> QR = strassenAlgorithm(polynomialASecondHalf, polynomialBFirstHalf);
    vector<int> PS = strassenAlgorithm(polynomialAFirstHalf, polynomialBSecondHalf);
    vector<int> QS = strassenAlgorithm(polynomialASecondHalf, polynomialBSecondHalf);
    vector<int> ans;
    int maxAnsDegree = PR.size() - 1;
    if (QR.size() < PS.size())
        QR.swap(PS);
    for (int i = 0; i < PS.size(); i++)
        QR[i] += PS[i];
    while (QR[QR.size() - 1] == 0 && QR.size() != 0)
        QR.pop_back();
    if (QR.size() != 0)
        if ((QR.size() + halfMaxSize - 1) > maxAnsDegree)
            maxAnsDegree = QR.size() + halfMaxSize - 1;
    if (QS.size() != 0)
        if ((QS.size() + 2 * halfMaxSize - 1) > maxAnsDegree)
            maxAnsDegree = QS.size() + 2 * halfMaxSize - 1;
    ;
    for (int i = 0; i <= maxAnsDegree; i++)
    {
        int tmp = 0;
        if (i >= 0 && i < PR.size())
            tmp += PR[i];
        if (i - halfMaxSize >= 0 && i - halfMaxSize < QR.size())
            tmp += QR[i - halfMaxSize];
        if (i - 2 * halfMaxSize >= 0 && i - 2 * halfMaxSize < QS.size())
            tmp += QS[i - 2 * halfMaxSize];
        ans.push_back(tmp);
    }
    return ans;
}
int main()
{
    vector<int> A;
    vector<int> B;
    int sizeA, sizeB;
    cout << "nhap kich co da thuc A:";
    cin >> sizeA;
    cout << "Nhap da thuc A:";
    for (int i = 1; i <= sizeA; i++)
    {
        int tmp;
        cin >> tmp;
        A.push_back(tmp);
    }
    cout << "Da thuc A la: " << A[0] << "+";
    for (int i = 1; i < A.size() - 1; i++)
        cout << A[i] << "x^" << i << "+";
    cout << A[A.size() - 1] << "x^" << A.size() - 1<<endl;
    cout << "nhap kich co da thuc B:";
    cin >> sizeB;
    cout << "Nhap da thuc B:";
    for (int i = 1; i <= sizeB; i++)
    {
        int tmp;
        cin >> tmp;
        B.push_back(tmp);
    }
    cout << "Da thuc B la: "<< B[0] << "+";
    for (int i = 1; i < B.size() - 1; i++)
        cout << B[i] << "x^" << i << "+";
    cout << B[B.size() - 1] << "x^" << B.size() - 1<<endl;
    vector<int> ans = strassenAlgorithm(A, B);
    cout << "Ket qua la: " << ans[0] << "+";
     for (int i = 1; i < ans.size() - 1; i++)
        cout << ans[i] << "x^" << i << "+";
    cout << ans[ans.size() - 1] << "x^" << ans.size() - 1;
    return 0;
}