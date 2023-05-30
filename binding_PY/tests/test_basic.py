import acf_py as m


def test_main():
    assert m.__version__ == "0.0.1"
    assert m.add(1, 2) == 3
    assert m.subtract(1, 2) == -1


class VClass(m.PyVirtualClassImpl):

    def Do(self, a):
        print("py ", a)


class VClass1(m.PyVirtualClassImpl):
    pass


def test_v_class():
    VClass().Do1(1)
    VClass1().Do1(2)
