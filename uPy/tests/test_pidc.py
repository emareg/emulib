
import matplotlib.pyplot as plt
from matplotlib.widgets import Slider
import numpy as np
# import mpld3
import emu.pidc as pidc


def stepfun(x):
    if x < 1 or x > 4: return 0
    # return 1
    # return x
    return x**2



def error(idx, soll, ist):
    return ist if idx > 0 else 0


def test():
    P_INIT=1.4
    I_INIT=2.0
    D_INIT=0.0

    ctl = pidc.PIDController([P_INIT, I_INIT, D_INIT])

    dt = 0.05
    # dts = list(range(0,10,dt))
    dts = np.arange(0,5,dt)

    soll = [stepfun(x) for x in dts]
    ist = [0] * len(dts)


    def updateIst():
        ist = [0] * len(dts)
        for i,y in enumerate(soll):
            if i == len(soll)-1: continue
            err = soll[i] - ist[i]
            ist[i+1] = ist[i] + ctl.step(err, dt)
        return ist


    # Plotting
    fig, ax = plt.subplots()
    plt.subplots_adjust(left=0.25, bottom=0.25)

    ax.plot(dts, soll)
    ist = updateIst() # call first time
    plot, = plt.plot(dts, ist)

    axP = plt.axes([0.25, 0.13, 0.65, 0.03])
    axI = plt.axes([0.25, 0.08, 0.65, 0.03])
    axD = plt.axes([0.25, 0.03, 0.65, 0.03])

    def updatePlot(val):
        ctl.reset()
        ctl.gainP = sliderP.val
        ctl.gainI = sliderI.val
        ctl.gainD = sliderD.val
        ist = updateIst()
        plot.set_ydata(ist)
        fig.canvas.draw_idle()    


    sliderP = Slider(axP, 'P', 0.0, 2.5, valinit=P_INIT, valstep=0.05)
    sliderI = Slider(axI, 'I', 0.0, 5.0, valinit=I_INIT, valstep=0.05)
    sliderD = Slider(axD, 'D', -0.03, 0.03, valinit=D_INIT, valstep=0.001)

    sliderP.on_changed(updatePlot)
    sliderI.on_changed(updatePlot)
    sliderD.on_changed(updatePlot)

    


    ax.set(xlabel='time (s)', ylabel='output (mV)',
           title='Simple PID plot')
    ax.grid()
    plt.show()

    # mpld3.show(fig)

test()