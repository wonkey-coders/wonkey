import os, sys, json, operator

DECL_PUBLIC      = 0x000001
DECL_PRIVATE     = 0x000002
DECL_PROTECTED   = 0x000004
DECL_INTERNAL    = 0x000008

DECL_VIRTUAL     = 0x000100
DECL_OVERRIDE    = 0x000200
DECL_ABSTRACT    = 0x000400
DECL_FINAL       = 0x000800
DECL_EXTERN      = 0x001000
DECL_EXTENSION   = 0x002000
DECL_DEFAULT     = 0x004000

DECL_GETTER      = 0x010000
DECL_SETTER      = 0x020000
DECL_OPERATOR    = 0x040000
DECL_IFACEMEMBER = 0x080000

DECL_ACCESSMASK  = DECL_PUBLIC|DECL_PRIVATE|DECL_PROTECTED|DECL_INTERNAL

#------------------------------------------------------------------------------

def get_flags(flags):
    f = ''
    if flags & DECL_PUBLIC:      f+='PUBLIC'      if f == '' else '|PUBLIC'
    if flags & DECL_PRIVATE:     f+='PRIVATE'     if f == '' else '|PRIVATE'
    if flags & DECL_PROTECTED:   f+='PROTECTED'   if f == '' else '|PROTECTED'
    if flags & DECL_VIRTUAL:     f+='VIRTUAL'     if f == '' else '|VIRTUAL'
    if flags & DECL_OVERRIDE:    f+='OVERRIDE'    if f == '' else '|OVERRIDE'
    if flags & DECL_ABSTRACT:    f+='ABSTRACT'    if f == '' else '|ABSTRACT'
    if flags & DECL_FINAL:       f+='FINAL'       if f == '' else '|FINAL'
    if flags & DECL_EXTERN:      f+='EXTERN'      if f == '' else '|EXTERN'
    if flags & DECL_EXTENSION:   f+='EXTENSION'   if f == '' else '|EXTENSION'
    if flags & DECL_DEFAULT:     f+='DEFAULT'     if f == '' else '|DEFAULT'
    if flags & DECL_GETTER:      f+='GETTER'      if f == '' else '|GETTER'
    if flags & DECL_SETTER:      f+='SETTER'      if f == '' else '|SETTER'
    if flags & DECL_OPERATOR:    f+='OPERATOR'    if f == '' else '|OPERATOR'
    if flags & DECL_IFACEMEMBER: f+='IFACEMEMBER' if f == '' else '|PUBLIC'
    return f if f != '' else 'NONE'

def is_public(flags):
    return flags & DECL_PUBLIC
def is_private(flags):
    return flags & DECL_PRIVATE
def is_protected(flags):
    return flags & DECL_PROTECTED
def is_virtual(flags):
    return flags & DECL_VIRTUAL
def is_override(flags):
    return flags & DECL_OVERRIDE
def is_abstract(flags):
    return flags & DECL_ABSTRACT
def is_final(flags):
    return flags & DECL_FINAL
def is_extern(flags):
    return flags & DECL_EXTERN
def is_extension(flags):
    return flags & DECL_EXTENSION
def is_default(flags):
    return flags & DECL_DEFAULT
def is_getter(flags):
    return flags & DECL_GETTER
def is_setter(flags):
    return flags & DECL_SETTER
def is_operator(flags):
    return flags & DECL_OPERATOR
def is_ifacemember(flags):
    return flags & DECL_IFACEMEMBER

def get_short_type(semtype):
    def get_last_type(stype):
        return stype.split('.')[-1]

    if '<' in semtype and '>' in semtype:
        typ, _, gen = semtype.partition('<')
        typ = get_last_type(typ)
        gen = gen[:-1].split(',')
        gen = [get_last_type(x) for x in gen]
        return typ+'<'+', '.join(gen)+'>'
    else:
        return semtype.split('.')[-1]

def debug_decl(file, decl):
    print('in file: '+file)
    print(json.dumps(decl, indent=2))

#------------------------------------------------------------------------------

def parse_func(file, decl):
    out = {}
    kind_func = decl['kind']
    if decl['ident'] in '<=>,*,/,+,-,&,~,<>,=,|,to'.split(','):
        kind_func = 'operator'
    out['kind'] = kind_func
    out['name'] = decl['ident']
    out['flags'] = decl['flags']
    out['type'] = decl['type']['kind']
    # generic args <...>
    if 'genArgs' in decl:
        out['genArgs'] = decl['genArgs']
    # return type
    if 'retType' in decl['type']:
        rtype = decl['type']['retType']
        kind = rtype['kind']
        if kind == 'ident':
            rttype = rtype['ident']
        elif kind == 'arraytype':
            rttype = rtype['type']['ident']+'[]'
        elif kind == 'generic':
            rttype = rtype['expr']['ident']+'<'+(','.join([arg['ident'].split('.')[-1] for arg in rtype['args']]))+'>'
        else:
            debug_decl(file, decl)
        out['retType'] = {
            'kind': kind,
            'semtype': rttype
        }
    # parameters
    if 'params' in decl['type']:
        out['params'] = []
        for param in decl['type']['params']:
            out_param = {}
            out_param['name'] = param['ident']
            if 'semtype' in param:
                out_param['semtype'] = get_short_type(param['semtype'])
            else:
                if 'kind' in param['type']:
                    out_param['semtype'] = param['type']['kind']
            out['params'].append(out_param)
    return out

#------------------------------------------------------------------------------

def parse_var(file, decl):
    out = {}
    out['kind'] = decl['kind']
    out['name'] = decl['ident']
    out['flags'] = decl['flags']

    semtype = ''
    if 'semtype' in decl:
        semtype = get_short_type(decl['semtype'])
    else:
        if 'type' in decl:
            kind = decl['type']['kind']
            if kind == 'ident':
                semtype = get_short_type(decl['type']['ident'])
            elif kind == 'arraytype':
                semtype = decl['type']['ident']+'[]'
            elif kind == 'generic':
                semtype = decl['type']['expr']['ident']+'<'+(','.join([arg['ident'].split('.')[-1] for arg in decl['type']['args']]))+'>'
            else:
                debug_decl(file, decl)
    out['semtype'] = semtype
    return out

#------------------------------------------------------------------------------

def parse_class(file, decl):
    out = {}
    out['kind'] = decl['kind']
    out['name'] = decl['ident']
    out['flags'] = decl['flags']
    out['members'] = []
    if 'namespace' in decl:
        out['namespace'] = decl['namespace']
    if 'superType' in decl: # extends ...
        out['superType'] = decl['superType']['ident']
    if 'ifaceTypes' in decl: # implements [...]
        out['ifaceTypes'] = ','.join([ident['ident'] for ident in decl['ifaceTypes']])
    if 'members' in decl:
        for member in decl['members']:
            kind = member['kind']
            out_member = {}
            if kind in ['field', 'const', 'global']:
                out_member = parse_var(file, member)
            if kind in ['method', 'function', 'operator', 'getter', 'setter']:
                out_member = parse_func(file, member)
            if len(out_member):
                out['members'].append(out_member)
    return out

#------------------------------------------------------------------------------

def parse_decl(file, decl):
    kind = decl['kind']
    if kind in ['class', 'struct', 'interface']:
        return parse_class(file, decl)
    else:
        return None

#------------------------------------------------------------------------------

def parse_file(file, decl):
    out = {}
    out['kind'] = 'file'
    out['file'] = file
    out['name'] = decl['ident']
    out['flags'] = decl['flags']
    out['decls'] = []
    if 'namespace' in decl:
        out['namespace'] = decl['namespace']
    if 'members' in decl:
        for member in decl['members']:
            out_member = parse_decl(file, member)
            if out_member is not None:
                out['decls'].append(out_member)
    if 'imports' in decl:
        for imp in decl['imports']:
            if not(imp.startswith('<') and imp.endswith('>')):
                imp_file = os.path.splitext(imp)[0]+'.geninfo'
                imp_ast = open(imp_file, 'r')
                imp_out = json.load(imp_ast)
                imp_ast.close()
                out_import = parse_file(imp_file, imp_out)
                out['decls'].append(out_import)
    if 'usings' in decl:
        out['usings'] = ['monkey.types']+decl['usings']
    return out

#------------------------------------------------------------------------------

def gen_ir(src):
    ast = open(src, 'r')
    inp = json.load(ast)
    ast.close()
    out = parse_file(src, inp)
    return out

#------------------------------------------------------------------------------

out_lines = ''

def l(s='', indent=0):
    global out_lines
    out_lines += (' ' * indent) + s

def ln(s='', indent=0):
    global out_lines
    out_lines += (' ' * indent) + s + '\n'

def reset_globals():
    global out_lines
    out_lines = ''

def get_visibility(flags):
    if is_public(flags): return '+'
    if is_private(flags): return '-'
    if is_protected(flags): return '#'

def get_members_kind(members, kind):
    return sorted(filter(lambda x: x['kind'] == kind, members), key=lambda x: x['name'])

#------------------------------------------------------------------------------ list

def emit_txt_var(decl):
    ln(get_visibility(decl['flags'])+decl['kind']+' '+decl['name']+': '+decl['semtype'])

def emit_txt_func(decl):
    l(get_visibility(decl['flags'])+decl['kind']+' '+decl['name'])
    # generic args
    if 'genArgs' in decl:
        l('<'+', '.join(decl['genArgs'])+'>')
    l(': ')
    # return type
    if 'retType' in decl:
        l(decl['retType']['semtype'])
    # parameters
    if 'params' in decl:
        params = ''
        for param in decl['params']:
            if params != '': params+=', '
            params+=param['name']+': '+param['semtype']
        l('('+params+')')
    ln()

def emit_txt_class(decl):
    l(decl['kind']+' '+decl['name'])
    if 'superType' in decl:
        l(' --> '+decl['superType'])
    if 'ifaceTypes' in decl:
        l(' implements '+decl['ifaceTypes'])
    ln()
    # attributes
    for at in get_members_kind(decl['members'], 'const'):
        emit_txt_var(at)
    for at in get_members_kind(decl['members'], 'global'):
        emit_txt_var(at)
    for at in get_members_kind(decl['members'], 'field'):
        emit_txt_var(at)
    ln('--')
    # operations
    for op in get_members_kind(decl['members'], 'function'):
        emit_txt_func(op)
    for op in get_members_kind(decl['members'], 'operator'):
        emit_txt_func(op)
    for op in get_members_kind(decl['members'], 'method'):
        emit_txt_func(op)
    ln()

def gen_txt(ir):
    if 'decls' in ir:
        for decl in ir['decls']:
            kind = decl['kind']
            if kind in ['class', 'struct', 'interface']:
                emit_txt_class(decl)
            if 'decls' in decl:
                gen_txt(decl)

#------------------------------------------------------------------------------ mermaid.js

def emit_mjs_var(decl, indent=0):
    l(get_visibility(decl['flags'])+decl['name'], indent)
    # static
    if decl['kind'] in ['const', 'global']:
        l('$')
    l(': '+decl['semtype'])
    ln()

def emit_mjs_func(decl, indent=0):
    l(get_visibility(decl['flags'])+decl['name'], indent)
    # generic args
    if 'genArgs' in decl:
        l('<'+', '.join(decl['genArgs'])+'>')
    # parameters
    if 'params' in decl:
        params = ''
        for param in decl['params']:
            if params != '': params+=', '
            params+=param['semtype']
        l('('+params+')')
    # abstract/static
    if is_abstract(decl['flags']) or is_virtual(decl['flags']):
        l('*')
    elif decl['kind'] in ['function']:
        l('$')
    # return type
    if 'retType' in decl:
        l(' '+decl['retType']['semtype'])
    ln()

def emit_mjs_class(decl):
    ln(decl['kind']+' '+decl['name']+ ' {', 2)
    # attributes
    for at in get_members_kind(decl['members'], 'const'):
        emit_mjs_var(at, 4)
    for at in get_members_kind(decl['members'], 'global'):
        emit_mjs_var(at, 4)
    for at in get_members_kind(decl['members'], 'field'):
        emit_mjs_var(at, 4)
    # operations
    for op in get_members_kind(decl['members'], 'function'):
        emit_mjs_func(op, 4)
    for op in get_members_kind(decl['members'], 'operator'):
        emit_mjs_func(op, 4)
    for op in get_members_kind(decl['members'], 'method'):
        emit_mjs_func(op, 4)
    ln('}', 2)
    if 'superType' in decl:
        ln(decl['superType']+' <|-- '+decl['name'],2)
    if 'ifaceTypes' in decl:
        for iface in decl['ifaceTypes'].split(','):
            ln(iface+' <.. '+decl['name'], 2)
    ln()

def gen_mjs(ir):
    global out_lines
    if out_lines == '':
        ln('classDiagram')

    if 'decls' in ir:
        for decl in ir['decls']:
            kind = decl['kind']
            if kind in ['class', 'struct', 'interface']:
                # class name
                emit_mjs_class(decl)
            if 'decls' in decl:
                gen_mjs(decl)

#------------------------------------------------------------------------------

if __name__ == '__main__':
    #os.chdir(os.path.split(__file__)[0])
    out = gen_ir('wake.geninfo')

    # save ir in file
    sav = open('gen_ir.json', 'w')
    sav.write(json.dumps(out, indent=2))
    sav.close

    # generate simple text
    gen_txt(out)
    sav = open('gen_txt.txt', 'w')
    sav.write(out_lines)
    sav.close

    reset_globals()

    # generate mermaid
    gen_mjs(out)
    sav = open('gen_mjs.txt', 'w')
    sav.write(out_lines)
    sav.close


