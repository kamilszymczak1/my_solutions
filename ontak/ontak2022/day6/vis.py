import pygame

class Point:
    def __init__ (self, x, y):
        self.x = x
        self.y = y
        
class Line:
    def __init__ (self, a, b, color):
        self.a = a
        self.b = b
        self.color = c
        
points = []
n = int(input())

for i in range(n):
    x, y = map(int, input().split())
    points.append(Point(x, y))

lines = []
m = int(input())

for i in range(m):
    c, x1, y1, x2, y2 = map(int, input().split())
    r = c >> 16
    g = (c >> 8) & ((1 << 8) - 1)
    b = c & ((1 << 8) - 1)
    lines.append(Line(Point(x1, y1), Point(x2, y2), (r, g, b)))

pygame.init()

pygame.display.set_caption("2D geometry visualiser")


HEIGHT = 1000
WIDTH = 1000
screen = pygame.display.set_mode((WIDTH, HEIGHT))

running = True


while running:
    
    pygame.Surface.fill(screen, (230, 230, 230))
    
    for line in lines:
        pygame.draw.line(screen, line.color, (line.a.x, HEIGHT - line.a.y), (line.b.x, HEIGHT - line.b.y))
    
    for point in points:
        pygame.draw.circle(screen, (0, 255, 0), (point.x, HEIGHT - point.y), 5)

    for event in pygame.event.get():
        
        if event.type == pygame.QUIT:
            running = False
    
    pygame.display.flip()
