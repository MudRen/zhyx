#include <ansi.h>

object book = find_object("/clone/book/lbook4");

object get_owner()
{
    object owner;
    if(objectp(book)) {
        owner = environment(book);
        if(owner->is_character()) return owner;
    }
    return 0;
}

object book_owner = get_owner();

string get_book()
{
    if(objectp(book)) destruct(book);
    if(objectp(book_owner) && userp(book_owner)) book_owner->unconcious();
    return "������...............Ѿ����ȥ���ɣ�";
}

static string book_owner_name = objectp(book_owner) ? book_owner->query("name") : "ĳ��";

static mixed *story = ({
        "�������������������£������ö������ˣ���Ȼѧҵ�Ļķ��ˡ�",
        "�������ס������Ǳ���ʦ�������ġ������ô�����ˣ��ҵúú����ң�",
        "������ʼ���䵹������......",
        "����������ͷ������ô�Ҳ������أ�",
        "������Ȼ����Ŷ��ԭ��ǰ������" + book_owner_name + "�ˣ�����Ҳ�ǣ�����ô�ö���������",
        "�������������ǡ���ǽ�����ܶ�Ҳ��������ȥ������С�������ж��ù���",
        "��������" + book_owner_name + "��ǰ��",
        book_owner_name + "����һȺС���ڵ���������أ���������Ū����������������",
                "������%��*������������*��%��###��*������%*",
                "����������С�ӣ�ԭ��Ϊ��������ڷ����ù���û�뵽����˲�������",
        "���������ˣ�����������Ҳֻ��������ˣ�����������",
        book_owner_name + "���У���������ʲô��û�У�ͬ����ֽ�ɻ�ֽ��̫���ˡ�",
        book_owner_name + "�ͳ�һ�����鶪������",
        (: get_book :),
        book_owner_name + "�����������ˡ�",
        "�����㬵Ļص���ң�ȡ�",
});

string prompt() { return HIW "���������¡�" NOR; }

void create()
{
        seteuid(getuid());
}

mixed query_story_message(int step)
{
        return step < sizeof(story) ? story[step] : 0;
}

