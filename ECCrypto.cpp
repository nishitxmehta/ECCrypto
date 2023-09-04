#include <bits/stdc++.h>
#define ll long long int
using namespace std;

ll multiplicativeInverse(ll A, ll M)
{
    ll temp = A;
    while (temp < 0)
        temp += M;
    if (temp == 0)
        return LONG_LONG_MAX;
    for (ll i = 1; i < M; i++)
    {
        temp = (i * A) % M;
        if (temp == 1)
            return i;
    }
} // finding inverse of a number

pair<ll, ll> additionOrDoubling(pair<ll, ll> P1, pair<ll, ll> P2, ll a, ll p)
{
    if (P1.first == P2.first && P1.second == p - P2.second)
        return make_pair(LONG_LONG_MAX, LONG_LONG_MAX);
    else if (P1.first != P2.first || P1.second != P2.second)
    {
        ll s1 = P2.second - P1.second;
        ll s2 = P2.first - P1.first;

        if ((s1 < 0 && s2 < 0) || (s1 >= 0 && s2 >= 0))
        {
            s1 = abs(s1);
            s2 = abs(s2);
            s1 %= p;
            s2 %= p;
        }
        else if (s1 < 0)
        {
            s1 = (s1 % p) + p;
            s2 %= p;
        }
        else
        {
            s1 %= p;
            s2 = (s2 % p) + p;
        }

        ll slope = (s1 * multiplicativeInverse(s2, p)) % p;

        ll x3 = slope * slope - P1.first - P2.first;
        if (x3 < 0)
            x3 = (x3 % p) + p;
        else
            x3 %= p;

        ll y3 = slope * (P1.first - x3) - P1.second;
        if (y3 < 0)
            y3 = (y3 % p) + p;
        else
            y3 %= p;

        return make_pair(x3, y3); // addition done
    }
    else
    {
        ll slope = ((3 * P1.first * P1.first + a) % p) * multiplicativeInverse((2 * P1.first) % p, p);
        if (slope < 0)
            slope = (slope % p) + p;
        else
            slope %= p;

        ll x3 = slope * slope - 2 * P1.first;
        if (x3 < 0)
            x3 = (x3 % p) + p;
        else
            x3 %= p;

        ll y3 = slope * (P1.first - x3) - P1.second;
        if (y3 < 0)
            y3 = (y3 % p) + p;
        else
            y3 %= p;

        return make_pair(x3, y3); // doubling done
    }
}

pair<ll, ll> keyGeneration(ll n, pair<ll, ll> G, ll a, ll p)
{
    if (n == 0)
    {
        G = make_pair(LONG_LONG_MAX, LONG_LONG_MAX);
        return G;
    }
    else
    {
        ll c = 1, s = 0;
        while (n > 0)
        {
            s += (n % 2) * c;
            n /= 2;
            c *= 10;
        } // converting decimal to binary

        string S = to_string(s);
        pair<ll, ll> g;
        g.first = G.first;
        g.second = G.second;

        for (ll i = 1; i < S.size(); i++)
        {
            if (S[i] == '1')
            {
                ll slope = ((3 * g.first * g.first + a) % p) * multiplicativeInverse((2 * g.second) % p, p);
                if (slope < 0)
                    slope = (slope % p) + p;
                else
                    slope %= p;

                ll x3 = slope * slope - 2 * g.first;
                if (x3 < 0)
                    x3 = (x3 % p) + p;
                else
                    x3 %= p;

                ll y3 = slope * (g.first - x3) - g.second;
                if (y3 < 0)
                    y3 = (y3 % p) + p;
                else
                    y3 %= p;

                g = make_pair(x3, y3); // doubling done

                ll s1 = g.second - G.second;
                if (s1 < 0)
                    s1 = (s1 % p) + p;
                else
                    s1 %= p;

                ll s2 = g.first - G.first;
                if (s2 < 0)
                    s2 = (s2 % p) + p;
                else
                    s2 %= p;

                slope = s1 * multiplicativeInverse(s2, p);
                if (slope < 0)
                    slope = (slope % p) + p;
                else
                    slope %= p;

                x3 = slope * slope - G.first - g.first;
                if (x3 < 0)
                    x3 = (x3 % p) + p;
                else
                    x3 %= p;

                y3 = slope * (G.first - x3) - G.second;
                if (y3 < 0)
                    y3 = (y3 % p) + p;
                else
                    y3 %= p;

                g = make_pair(x3, y3); // addition done
            }
            else
            {
                ll slope = ((3 * g.first * g.first + a) % p) * multiplicativeInverse((2 * g.second) % p, p);
                if (slope < 0)
                    slope = (slope % p) + p;
                else
                    slope %= p;

                ll x3 = slope * slope - 2 * g.first;
                if (x3 < 0)
                    x3 = (x3 % p) + p;
                else
                    x3 %= p;

                ll y3 = slope * (g.first - x3) - g.second;
                if (y3 < 0)
                    y3 = (y3 % p) + p;
                else
                    y3 %= p;

                g = make_pair(x3, y3); // doubling done
            }
        }
        return g;
    }
}

ll a = 45, b = 51, p = 10009; // proved elliptic curves parameters

int main()
{
    ll c, pA, pB, k, kk;
    vector<ll> x, y, e, f;
    unordered_multimap<ll, ll> mpp1;
    vector<pair<ll, ll>> Pm1, Pm2, Cm;
    pair<ll, ll> P1, P2, P3, P4, P5, Pm, G, PA, PB, kA, kB;
    string m;

    for (ll i = 0; i < p; i++)
    {
        x.emplace_back((i * i * i + a * i + b) % p);
        y.emplace_back((i * i) % p);
    }

    for (ll i = 0; i < p; i++)
        for (ll j = 0; j < p; j++)
            if (x[i] == y[j])
                mpp1.insert(pair<ll, ll>(i, j));

    for (auto itr = mpp1.begin(); itr != mpp1.end(); ++itr)
        G = make_pair(itr->first, itr->second);

    srand(time(0));

    pA = rand() % mpp1.size() + 1; // A's private key
    cout << "A's private key = " << pA << "\n";
    pB = rand() % mpp1.size() + 1; // B's private key
    cout << "B's private key = " << pB << "\n";
    PA = keyGeneration(pA, G, a, p); // A's public key
    cout << "A's public key = (" << PA.first << ", " << PA.second << ")\n";
    PB = keyGeneration(pB, G, a, p); // B's public key
    cout << "B's public key = (" << PB.first << ", " << PB.second << ")\n\nMessage from .txt file:\n";

    k = rand() % mpp1.size() + 1;
    P1 = keyGeneration(k, G, a, p);
    P2 = keyGeneration(k, PB, a, p);
    P3 = keyGeneration(k, PA, a, p);

    ifstream file("message.txt");
    if (file.fail())
        cout << "Error in your file.";
    else
    {
        char c;
        while (file.get(c))
            m += c;

        cout << m << "\n";
        file.close();
    } // reading character by character from text file

    for (ll i = 0; i < m.size(); i++)
    {
        e.emplace_back((ll)m[i] * (rand() % 78 + 1));
        f.emplace_back(0);

        while (true)
        {
            c = 0;
            for (auto itr = mpp1.begin(); itr != mpp1.end(); ++itr)
                if (itr->first == e[i])
                {
                    Pm1.emplace_back(pair<ll, ll>(itr->first, itr->second)); // encoding message
                    c++;
                    break;
                }
            if (c > 0)
                break;
            e[i]++;
            f[i]++;
        }
    }

    cout << "\nEncoded Message:\n";
    for (auto itr = Pm1.begin(); itr != Pm1.end(); ++itr)
        cout << "(" << itr->first << ", " << itr->second << ") ";

    for (auto itr = Pm1.begin(); itr != Pm1.end(); ++itr)
    {
        Pm = make_pair(itr->first, itr->second);
        P4 = additionOrDoubling(Pm, P2, a, p);
        Cm.emplace_back(pair<ll, ll>(P4.first, P4.second));
    } // encrypting message

    cout << "\n\nEncrypted Message:\n";
    for (auto itr = Cm.begin(); itr != Cm.end(); ++itr)
        cout << "(" << itr->first << ", " << itr->second << ") ";

    cout << "\n\nEnter B's private key to decrypt the message\nB's private key = ";
    cin >> kk;
    if (kk == pB)
    {
        P5 = keyGeneration(kk, P1, a, p);
        P5.second = p - P5.second;
        for (auto itr = Cm.begin(); itr != Cm.end(); ++itr)
        {
            P4 = make_pair(itr->first, itr->second);
            P4 = additionOrDoubling(P4, P5, a, p);
            Pm2.emplace_back(pair<ll, ll>(P4.first, P4.second));
        } // decryprting message

        cout << "\nDecrypted Message:\n";
        for (auto itr = Pm2.begin(); itr != Pm2.end(); ++itr)
            cout << "(" << itr->first << ", " << itr->second << ") ";

        cout << "\n\nDecoded Message:\n";
        c = 0;
        for (auto itr = Pm2.begin(); itr != Pm2.end(); ++itr)
            cout << (char)((itr->first - f[c]) / ((e[c] - f[c]) / (ll)m[c++])); // decoding message
    }
    else
        cout << "Entered key is wrong!";
}