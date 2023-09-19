import matplotlib.pyplot as plt
import numpy as np

X = np.linspace(0, 10, 100)
Y1 = X*X
Y2 = X + 10
Y3 = np.random.randn(10000)

M1 = np.array([[1, 2], [3, 4]])
M2 = np.array([[5, 6], [7, 8]])
M3 = np.array([[9, 10], [11, 12]])

plt.figure(figsize=(8, 6))  # 定义图的大小

# # show only once
# plt.title('Example')
# plt.subplot(231)
# plt.imshow(M1, cmap="Greens")
# plt.subplot(232)
# plt.imshow(M2, cmap="Blues")
# plt.subplot(233)
# plt.imshow(M3, cmap="Reds")
# plt.subplot(234)
# plt.plot(X, Y1)
# plt.subplot(235)
# plt.plot(X, Y2)
# plt.subplot(236)
# plt.xlabel("time(s)")
# plt.ylabel("Volt")
# plt.plot(X, Y3)
# # plt.plot(X,Y,lable="$sin(X)$",color="red",linewidth=2)

# plt.show()

# show twice
plt.ion()
for i in range(20):
    plt.suptitle('Example {}'.format(i))
    plt.subplot(231)
    plt.imshow(M1, cmap="Greens")
    plt.subplot(232)
    plt.imshow(M2, cmap="Blues")
    plt.subplot(233)
    plt.imshow(M3, cmap="Reds")
    plt.subplot(234)
    plt.plot(X, Y1)
    plt.subplot(235)
    plt.plot(X, Y2)
    plt.subplot(236)
    plt.title("Example_sub {}".format(i))
    plt.xlabel("time(s)")
    plt.ylabel("Volt")
    plt.hist(Y3)
    # plt.plot(X,Y,lable="$sin(X)$",color="red",linewidth=2)

    plt.pause(0.5)
plt.pause(0)
# plt.ioff()
