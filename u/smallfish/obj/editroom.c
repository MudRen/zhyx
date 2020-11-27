// roommaker.c
// for ESLib

#define RMK_VERSION "(v2.0)"
#include <ansi.h>
inherit ITEM;

string *special_props = ({
    "short", "long" });
mapping map_dirs = ([
    "north":        "��",
    "south":        "��",
    "east":         "��",
    "west":         "��",
    "northup":      "��������",
    "southdown":        "�ϱ�����",
    "southup":      "�ϱ�����",
    "northdown":        "��������",
    "eastup":       "��������",
    "westdown":     "��������",
    "westup":       "��������",
    "eastdown":     "��������",
    "northeast":        "����",
    "northwest":        "����",
    "southeast":        "����",
    "southwest":        "����",
    "up":           "��",
    "down":         "��",
    "out":          "��",
]);

int save_room_file(string yn, string file, string str);

void create()
{
    set_name("����༭��" + RMK_VERSION, ({ "roommaker", "maker" }) );
    set_weight(100);
    set("unit", "��" );
    set("long", @LONG
����һ�����������١����췿��Ĺ��ߣ�����ʱ�䲻���������  lag ����ʦ
����������������򵥵ķ��䣬���������������Լ����򷿼��Ʒ�ʣ����
��Ҫ̫������������������ʹ�����¼���ָ�

mkroom <���䵵��>
    ���һ�����ա����䣬֮������� goto ����������� rset �趨�����
    ���������ԡ�

rset <��������> <��������>
    �趨��Ŀǰ���ڷ�������ԣ��� short,outdoors,valid_startroom�ȡ�

rdelete <��������>
    ɾ����Ŀǰ���ڷ�������ԣ���rset�趨�����Ժ�long,objects,exits�ȡ�

long
    �趨��Ŀǰ���ڷ�����������ԡ�

connect <����> <���䵵��>||<none>
    ����Ŀǰ���ڵķ�������һ�����ڵ���һ�����䣬���䵵��=none��ɾ���������

addobj <NPC����> <����>
    �趨��Ŀǰ���ڷ����NPC����������

saveroom
    ����Ŀǰ���ڵķ���浵��
LONG
    );
}


void init()
{
    if( wizardp(environment()) ) {
        seteuid(getuid(environment()));
        add_action("do_mkroom", "mkroom");
        add_action("do_rset", "rset");
        add_action("do_delete", "rdelete");
        add_action("do_connect", "connect");
        add_action("do_saveroom", "saveroom");
        add_action("do_addobj", "addobj");
        add_action("do_long", "long");
    }
}

int do_mkroom(string arg)
{
    string file, dir;

    if( !arg ) return notify_fail("ָ���ʽ��mkroom <���䵵��> [<����>]\n");
    if( sscanf(arg, "%s %s", file, dir)!=2 )
        file = arg;
    seteuid(geteuid(this_player()));
    file = resolve_path(this_player()->query("cwd"), file) + ".c";
    if( file_size(file)!=-1 )
        return notify_fail("���� " + file + " �Ѿ������ˡ�\n");
    if( !write_file(file, @ROOM_CODE
// This is a room made by roommaker.

inherit ROOM;

void create()
{
    set("short", "�շ���");
    set("long", "����һ��ʲ��Ҳû�еĿշ��䡣\n");
    setup();
    replace_program(ROOM);
}
ROOM_CODE
) ) return notify_fail("��û��д�뵵��(" + file +")��Ȩ����\n");
    message_vision("ֻ����$N������һ�ţ����١���һ�����������������ֱ����һ�㡣\n", this_player());
    return 1;
}

int do_rset(string arg)
{
    string prop, str;
    mixed data;

    if( !arg || sscanf(arg, "%s %s", prop, str)!=2 )
        return notify_fail("ָ���ʽ��rset <��������> <��������>\n
\t rset short           ���趨��䷿��ļ���������\n
\t rset outdoors        ���趨�����ǻ������ԣ�\n
\t rset valid_startroom ���趨�������´����߿�ʼ�����ԣ�\n
\t �������磺rset no_fight rset no_magic ��...\n\n");
    write("����"+prop+"������Ϊ"+str);
    if( sscanf(str, "%d", data)!=1 )
        data = str;
    environment(this_player())->set(prop, str);
    write("...Ok.\n");
    return 1;
}

int do_delete(string arg)
{

    if( !arg)
        return notify_fail("ָ���ʽ��rdelete <��������>\n");
    environment(this_player())->delete(arg);
    write("Ok.\n");
    return 1;
}
int do_long()
{
    string arg;
    arg="";
    write("ѶϢ�����кü��У������� . ��ʾ������\n");
    write("������������������������������������������������������������������������\n");
    input_to("get_long",arg);
    return 1;
}
int get_long(string msg,string arg)
{
    if( msg=="."){
        environment(this_player())->set("long", arg);
        write("Ok.\n");
        return 1;
    }
    arg+=msg+"\n";
    input_to("get_long",arg);
    return 1;
}

int do_connect(string arg)
{
    mapping exits;
    int i;
    object room;
    string dir, file,*dirs;

    exits = environment(this_player())->query("exits");
    if( !arg || sscanf(arg, "%s %s", dir, file)!=2 ){
        dirs=sort_array( keys(map_dirs),(: strcmp :) );
        dir=" һ������£�ʹ�õĳ��ڷ��������¼���: \n";
        for (i=0;i<sizeof(map_dirs);i++)
            dir+=sprintf("%-12s \t %-12s \n",dirs[i],map_dirs[dirs[i]]);
        if( mapp(exits) ){
            dir+="����ĳ����У�\n";
            dirs=keys(exits);
            for (i=0;i<sizeof(exits);i++){
                if (!room=find_object(exits[dirs[i]]))
                room=load_object(exits[dirs[i]]);
            if (room)   dir+=sprintf(BOLD"\t%-12s"+NOR+YEL+" --> "+CYN+"%s"+RED+"(%s) \n"+NOR,dirs[i],room->query("short"),exits[dirs[i]]);
            else    dir+=sprintf(BOLD"\t%-12s"+NOR+YEL+" --> "+RED+"û���������ڡ�\n"+NOR,dirs[i]);
            }
        }
        return notify_fail(dir+"\nָ���ʽ��connect <����> <���䵵��>||<none>\n");
    }
    if (file=="none"){
        environment(this_player())->delete("exits/"+dir);
        write("ɾ������...Ok.\n");
        return 1;
    }
    file = resolve_path(this_player()->query("cwd"), file);
        if (!room=find_object(file))
        room=load_object(file);
    if (!room)  return notify_fail("��û��"+file+"�������...\n");
    if( mapp(exits) )
        exits[dir] = file;
    else
        environment(this_player())->set("exits", ([ dir: file ]) );
    switch(dir){
        case "north"    :   dir="south";break;
        case "northwest":   dir="southeast";break;
        case "northeast":   dir="southwest";break;
        case "northdown":   dir="southup";break;
        case "northup"  :   dir="southdown";break;
        case "south"    :   dir="north";break;
        case "southwest":   dir="northeast";break;
        case "southeast":   dir="northwest";break;
        case "southdown":   dir="northup";break;
        case "southup"  :   dir="northdown";break;
        case "west" :   dir="east";break;
        case "westup"   :   dir="eastdown";break;
        case "westdown" :   dir="eastup";break;
        case "eastup"   :   dir="westdown";break;
        case "eastdown" :   dir="westup";break;
        case "east" :   dir="west";break;
        case "up"   :   dir="down";break;
        case "down" :   dir="up";break;
        case "out"  :   dir="enter";break;
        case "enter"    :   dir="out";break;
        default     :   dir="";break;
    }
    if (dir!=""){
        exits = room->query("exits");
        file=base_name(environment(this_player()));
        if( mapp(exits) )
            exits[dir] = file;
        else
        room->set("exits", ([ dir: file ]) );
    }
    write("Ok.\n");
    return 1;
}
int do_addobj(string arg)
{
    mapping objects;
    string file,*files;
    int amount;

    objects = environment(this_player())->query("objects");
    if( !arg || sscanf(arg, "%s %d", file,amount)!=2 ){
    if( mapp(objects) )
        files=keys(objects);
        file=" ��������NPC�У�\n";
        for (amount=0;amount<sizeof(objects);amount++)
            file+=sprintf(BOLD+"%20s %10s��\n"+NOR,files[amount]->short(),chinese_number(objects[files[amount]]) );
        return notify_fail(file+"\nָ���ʽ��addobj <NPC����> <����>\n");
    }
    if ( file_size(file+".c")<0 )   file = resolve_path(this_player()->query("cwd"), file);
    if ( file_size(file+".c")<0 )
        return notify_fail("û��������......\n");
        if (amount==0){
            environment(this_player())->delete("objects/"+file);
            write("ɾ��NPC��Ok.\n");
            return 1;
        }
    if( mapp(objects) )
        objects[file] = amount;
    else
        environment(this_player())->set("objects", ([ file: amount ]) );
    write("Ok.\n");
    return 1;
}
int update(object me, string file)
{
        int i;
        object obj, *inv;
        string err;

        seteuid( geteuid(me) );

        if( !sscanf(file, "%*s.c") ) file += ".c"; 

        if( file_size(file)==-1 )
                return notify_fail("û�����������\n");

        if (obj = find_object(file)) {
                if( obj==environment(me) ) {
                        if( file_name(obj)==VOID_OB )
                                return notify_fail("�㲻���� VOID_OB 
�����±��� VOID_OB��\n");
                        inv = all_inventory(obj);
                        i = sizeof(inv);
                        while(i--)
                                if( userp(inv[i]) ) inv[i]->move(VOID_OB, 1);
                                else inv[i] = 0;
                }
                destruct(obj);
        }

        if (obj) return notify_fail("�޷�����ɳ�ʽ�롣\n");

    write("���±��� " + file + "��");
        err = catch( call_other(file, "???") );
        if (err)
                printf( "��������\n%s\n", err );
        else {
                write("�ɹ���\n");
                if( (i=sizeof(inv)) && (obj = find_object(file))) {
                        while(i--)
                                if( inv[i] && userp(inv[i]) ) 
inv[i]->move(obj, 1);
                }
        }
                
        return 1;
}


int do_saveroom(string arg)
{
    object env;
    string str, *name, file;
    mapping prop;
    int i;

    env = environment(this_player());
    file = file_name(env) + ".c";
    str = "// Room: " + file +@ROOM_CODE

// This is a room made by roommaker. write by Fan. :)

inherit ROOM;

void create()
{
ROOM_CODE
;
    str += sprintf("\tset(\"short\", %O);\n", env->query("short") );
    str += sprintf("\tset(\"long\", @LONG\n%sLONG\n);\n", env->query("long") );
    prop = env->query_entire_dbase();
    name = keys(prop);
    for(i=0; i<sizeof(name); i++) {
        if( member_array(name[i], special_props)!=-1 ) continue;
        str += sprintf("\tset(\"%s\", %O);\n", name[i], prop[name[i]] );
    }
    str += "\n\tsetup();\n\treplace_program(ROOM);\n}\n";

    // Replace current directory with __DIR__ macro to make relocatable code.
    i = strlen(file)-1;
    while( (i > 0) && (file[i]!='/')) i--;
    if( i>0 ) {
        write("ĿǰĿ¼��" + file[0..i] + " �� __DIR__ ȡ����\n");
        str = replace_string(str, "\"" + file[0..i], "__DIR__\"");
    }

    if( file_size(file)!=-1 ) {
        write("���� " + file + " �Ѵ��ڣ�Ҫɾ���ɵ���[y/n]");
        input_to("save_room_file", file, str);
        return 1;
    }

    return save_room_file("y", file, str);
}

int save_room_file(string yn, string file, string str)
{
    if( strlen(yn)<1 || yn[0]!='y' ) return 1;

    rm(file);
    write("�浵 " + file + "....");
    if( write_file(file, str) ) {
        write("Ok.\n");
        return update(this_player(),file);
    } else
        return notify_fail("��û��д���������(" + file + ")��Ȩ����\n");
}

void owner_is_killed() { destruct(this_object()); }

