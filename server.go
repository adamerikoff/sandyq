package main

import (
	"fmt"
	"log/slog"
	"net"
)

const defaultListenAddress = ":8831"

type Server struct {
	Config
	peers     map[*Peer]bool
	ln        net.Listener
	addPeerCh chan *Peer
	quitCh    chan struct{}
	msgCh     chan []byte
}

func NewServer(cfg Config) *Server {
	if len(cfg.ListenAddress) == 0 {
		cfg.ListenAddress = defaultListenAddress
	}
	return &Server{
		Config:    cfg,
		peers:     make(map[*Peer]bool),
		ln:        nil,
		addPeerCh: make(chan *Peer),
		msgCh:     make(chan []byte),
		quitCh:    make(chan struct{}),
	}
}

func (s *Server) Start() error {
	ln, err := net.Listen("tcp", s.Config.ListenAddress)
	if err != nil {
		return err
	}
	s.ln = ln

	go s.loop()

	slog.Info("server is running", "listenAddress=", s.Config.ListenAddress)

	return s.acceptLoop()
}

func (s *Server) loop() {
	for {
		select {
		case rawMsg := <-s.msgCh:
			if err := s.handleRawMessage(rawMsg); err != nil {
				slog.Error("raw message error", "err", err)
			}
		case peer := <-s.addPeerCh:
			s.peers[peer] = true
		case <-s.quitCh:
			return
		}
	}
}

func (s *Server) acceptLoop() error {
	for {
		conn, err := s.ln.Accept()
		if err != nil {
			fmt.Errorf("accept error", "err", err)
			continue
		}
		go s.handleConn(conn)
	}
}

func (s *Server) handleConn(conn net.Conn) {
	peer := NewPeer(conn, s.msgCh)
	s.addPeerCh <- peer

	slog.Info("new peer connected", "remoteAddress", conn.RemoteAddr())

	if err := peer.readLoop(); err != nil {
		slog.Error("peer read error", "err", err, "remoteAddress", conn.RemoteAddr())
	}
}

func (s *Server) handleRawMessage(rawMsg []byte) error {
	return nil
}
