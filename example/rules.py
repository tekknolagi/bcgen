g = BCGen(r = 7, f = 0)

g.rule('addr',   '_RRR__', 'R0 = R1 + R2;')
g.rule('addi',   '_RR__I', 'R0 = R1 + IMM;')
g.rule('movi',   '_R___I', 'R0 = IMM;')
g.rule('bltr',   'rRR__I', 'if (R0 < R1) JUMP(IMM);')

g.write()
