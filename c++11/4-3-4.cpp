enum class{K1,K2,K3} anon_e;

union
{
    decltype(anon_e) key;
    char* name;
}anon_u;

struct 
{
    int d;
    decltype(anon_u) id;
}anon_s[20];

int main()
{
    decltype(anon_s) as;
    as[0].id.key = decltype(anon_e)::K2;
}
